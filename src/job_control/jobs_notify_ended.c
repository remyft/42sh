/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_notify_ended.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:13:22 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/11 17:42:49 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "signal_intern.h"
#include <stdio.h>

int		jobs_notify_ended(t_jobs *jobs)
{
	int			status;
	t_jobs		*job;
	t_process	*p;
	pid_t		pid;

	//signal_to_default();
	while ((pid = waitpid(WAIT_ANY, &status, WNOHANG)) > 0)
	{
		job = job_by_pid(jobs, pid);
		p = process_by_pid(job->m_process, pid);
		process_set_status(job, p, status);
		printf("Setting status\n");
		job_notify(job);
		if (job_finished(job))
		{
			job->status |= JOB_NOTIFIED;
			printf("[%d]   %-22s command\n", job->id, "done");
		}
	}
	return (1);
}
