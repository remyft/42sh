/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 20:23:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/18 17:50:27 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "shell_env.h"
#include "command.h"
#include "job_control.h"
#include <errno.h>
#include <unistd.h>

static void		command_ret(int *ret)
{
	if (!ret)
		return ;
	if (WIFEXITED(*ret))
		*ret = WEXITSTATUS(*ret);
	else if (WIFSIGNALED(*ret))
	{
		*ret = WTERMSIG(*ret) + 128;
		write(1, "\n", 1);
	}
	else if (WIFSTOPPED(*ret))
		*ret = WTERMSIG(*ret) + 128;
}

void			command_process(pid_t pid, t_jobs *job, t_process *p, t_s_env *e)
{
	p->pid = pid;
	if (e->interactive)
	{
		if (!job->pgid)
			job->pgid = pid;
		setpgid(pid, job->pgid);
	}
}

void			command_wait2(pid_t pid, t_execute *exec, t_s_env *e)
{
	t_jobs		*job;
	t_process	*proc;

	(void)exec;
	job = job_by_id(e->job_id, e->jobs);
	proc = job->process;
	proc->pid = pid;
	if (job->pgid > 0)
		setpgid(pid, job->pgid);
	else
	{
		job->pgid = proc->pid;
		setpgid(pid, job->pgid);
	}
	if (!e->async)
	{
		tcsetpgrp(0, job->pgid);
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp(0, getpid());
		signal(SIGTTOU, SIG_DFL);
	}
	return (command_ret(&e->ret));
}

void			command_wait(pid_t pid, int async, int *ret)
{
	pid_t		got;

	if (!async)
		while ((got = waitpid(pid, ret, 0)) > 0)
			if (got == pid)
				return (command_ret(ret));
}
