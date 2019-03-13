/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 20:23:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/10 19:06:42 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "shell_env.h"
#include "command.h"
#include "job_control.h"
#include <errno.h>

static int waitjob(t_jobs *jobs)
{
    int wait_pid = -1;
    int status = 0;

	//if (job->pgid > 0)
	//	wait_pid = waitpid(jobs->process->pid, &status, WUNTRACED);
	//else
	wait_pid = waitpid(jobs->process->pid, &status, WUNTRACED);
	//	printf("%d\n", job->next->process->status);
 //   if (WIFEXITED(status))
	//	jobs->process->status = 2;
	//if (WIFSIGNALED(status))
	//	set_pstatus(jobs->process, wait_pid, STATUS_FINISHED);
	//	jobs->process->status = STATUS_FINISHED;
	return (status);
}

static void		command_ret(int *ret)
{
	if (!ret)
		return ;
	if (WIFEXITED(*ret))
		*ret = WEXITSTATUS(*ret);
	else if (WIFSIGNALED(*ret))
		*ret = WTERMSIG(*ret) + 128;
	else if (WIFSTOPPED(*ret))
		*ret = WTERMSIG(*ret) + 128;
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
		e->ret = waitjob(job);
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
