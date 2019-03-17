/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:39:27 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/09 11:32:42 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static int	job_stopped(t_jobs *job)
{
	t_process	*p;

	p = job->process;
	while (p)
	{
		if (p->status < 0)
			return (-1);
		p = p->next;
	}
	return (0);
}

static void	job_wait(t_jobs *job, t_s_env *e)
{
	(void)e;
	int		status;
	pid_t	pid;

	pid = waitpid(-job->pgid, &status, WUNTRACED);
	while (!proc_update(job, pid, status)
			&& !job_stopped(job)
			&& !job_completed(job))
		pid = waitpid(-job->pgid, &status, WUNTRACED);

}

static void	job_foreground(t_jobs *job, t_s_env *e)
{
	tcsetpgrp(0, job->pgid);
	job_wait(job, e);
	tcsetpgrp(0, e->pgid);
	
}

static void	job_background(t_jobs *job, t_s_env *e)
{
	(void)job;
	(void)e;
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

void		get_job_status(t_jobs *jobs)
{
	int		status;
	int		id;
	pid_t	pid;

	while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
	{
		// see later for return value of process
		if (WIFEXITED(status))
			// status
			;
		else if (WIFSTOPPED(status))
			// status
			;
		else if (WIFCONTINUED(status))
			// need to set status
			;
		//id = get_job_id(pid);
	//	if (id && job_end(id))
			//end_job(id);
		(void)jobs;
		(void)id;
	}
}
