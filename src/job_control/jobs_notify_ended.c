/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_notify_ended.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:13:22 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/20 10:13:28 by dbaffier         ###   ########.fr       */
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

int		job_ch_suspended(t_jobs *job)
{
	t_m_process	*m_p;
	
	//if (job->status & JOB_FORKED)
		//return (job_forked_suspended(job));
	m_p = job->m_process;
	while (m_p)
	{
		if (job_suspended(job, m_p))
			return (job_notify(job, m_p));
		m_p = m_p->next;
	}
	return (1);
}

t_m_process	*m_proc_by_pid(t_m_process *begin, pid_t pid)
{
	t_process	*p;

	while (begin)
	{
		p = begin->p;
		while (p)
		{
			if (p->pid == pid)
				return (begin);
			p = p->next;
		}
		begin = begin->next;
	}
	return (begin);
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
			process_set_status(job, (t_process *)job->job_forked, status, NULL);
		}
		else
		{
			p = process_by_pid(job->m_process, pid);
			process_set_status(job, p, status, m_proc_by_pid(job->m_process, pid));
		}
	//	job_notify(job);
		if (job_finished(job))
		{
			job->status |= JOB_NOTIFIED;
			job_no_opt(job);
	//		printf("[%d]   %-22s %s\n", job->id, "done", job->cmd_name);
		}
		else if (job_ch_suspended(job))
			;
	}
	return (1);
}
