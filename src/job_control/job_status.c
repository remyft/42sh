/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:39:27 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/20 11:51:53 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static int	job_finished(t_s_env *e, pid_t pid, int status)
{
	t_jobs	*job;

	(void)status;
	job = job_by_pid(e, pid);
	for (t_process *p = job->process; p; p = p->next)
	{
		if (p->status != STATUS_FINISHED)
			return (0);
	}
	return (1);
}

static void	job_wait(t_jobs *job, t_s_env *e)
{
	(void)e;
	int		status;
	pid_t	pid;

	//jobs_terminated(e);
	do 
	{
		pid = waitpid(-job->pgid, &status, WUNTRACED);
	}
	while (!proc_update(e, job, pid, status)
		&& !job_finished(e, pid, status));

}

static void	job_foreground(t_jobs *job, t_s_env *e)
{
	tcsetpgrp(0, job->pgid);
	signal(SIGTTOU, SIG_IGN);
	job_wait(job, e);
	tcsetpgrp(0, e->pid);
	signal(SIGTTOU, SIG_DFL);
	remove_job(&e->jobs, job->id);
}

static void	job_background(t_jobs *job, t_s_env *e)
{
	(void)e;
	printf("[%d] %d\n", job->id, job->pgid);
}

void		job_handler(t_jobs *job, t_s_env *e)
{
	if (!e->interactive)
		job_wait(job, e);
	else if (!e->async)
		job_foreground(job, e);
	else
		job_background(job, e);

}
