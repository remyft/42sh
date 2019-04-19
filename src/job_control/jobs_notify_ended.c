/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_notify_ended.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:13:22 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/19 09:21:02 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "signal_intern.h"
#include "builtin_jobs.h"
#include <stdio.h>

int		jobs_notify_forked(t_jobs *job)
{
	(void)job;
	//job->job_forked->status  =
	return (1);
}

int		jobs_notify_ended(t_jobs *jobs)
{
	int			status;
	t_jobs		*job;
	t_process	*p;
	pid_t		pid;

	while ((pid = waitpid(WAIT_ANY, &status, WCONTINUED | WUNTRACED | WNOHANG)) > 0)
	{
		job = job_by_pid(jobs, pid);
		if (job->status & JOB_FORKED)
		{
			job->job_forked = job->m_process->p;
			process_set_status(job, (t_process *)job->job_forked, status);
		}
		else
		{
			p = process_by_pid(job->m_process, pid);
			process_set_status(job, p, status);
		}
		job_notify(job);
		if (job_finished(job))
		{
			job->status |= JOB_NOTIFIED;
			job_no_opt(job);
	//		printf("[%d]   %-22s %s\n", job->id, "done", job->cmd_name);
		}
	}
	return (1);
}
