/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_suspended.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:40:39 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/20 10:30:52 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <stdio.h>

int		job_forked_suspended(t_jobs *job)
{
	t_process	*p;

	p = (t_process *)job->job_forked;
	return ((p->status != STATUS_SUSPENDED ? 0 : 1));
}

int		job_sig_suspended(t_jobs *job, t_m_process *m_p)
{
	t_process	*p;

	(void)job;
	p = m_p->p;
	while (p)
	{
		if (p->s_suspended > 0)
			return (p->s_suspended);
		p = p->next;
	}
	return (0);
}

int		job_suspended(t_jobs *job, t_m_process *m_p)
{
	t_process	*p;

	if (job->status & JOB_FORKED)
		return (job_forked_suspended(job));
	p = m_p->p;
	while (p)
	{
		if (p->status != STATUS_STOPPED)
			return (0);
		p = p->next;
	}
	return (1);
}

