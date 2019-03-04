/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 20:23:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/04 13:59:23 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "shell_env.h"
#include "command.h"
#include "job_control.h"


static int waitjob(t_jobs *jobs, int id)
{

    int wait_pid = -1;
    int status = 0;

	(void)id;
	wait_pid = waitpid(-jobs->pgid, &status, WUNTRACED);
    if (WIFSIGNALED(status))
	{
		jobs->process->status = JOB_TERMINATED;
	}
	return (status);
}

void			command_wait2(pid_t pid, t_execute *exec, t_s_env *e)
{
	t_jobs		*job;
	t_process	*proc;

	job = get_job_by_id(exec->job_id, e->jobs);
	proc = job->process;
	proc->pid = pid;
	if (job->pgid > 0)
		setpgid(pid, job->pgid);
	else
	{
		job->pgid = proc->pid;
		setpgid(pid, job->pgid);
	}
	if (!exec->command->async)
	{
		tcsetpgrp(0, job->pgid);
		waitjob(job, exec->job_id);
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp(0, getpid());
		signal(SIGTTOU, SIG_DFL);
	}
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

void			command_wait(pid_t pid, int async, int *ret)
{
	pid_t		got;

	if (!async)
		while ((got = waitpid(pid, ret, 0)) > 0)
			if (got == pid)
				return (command_ret(ret));
}
