/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_suspended.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:40:39 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/18 10:06:56 by dbaffier         ###   ########.fr       */
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

int		job_suspended(t_jobs *job)
{
	t_process	*p;
	t_m_process	*m_p;

	if (job->status & JOB_FORKED)
		return (job_forked_suspended(job));
	m_p = job->m_process;
	while (m_p)
	{
		p = m_p->p;
		while (p)
		{
			if (p->status != STATUS_SUSPENDED)
				return (0);
			p = p->next;
		}
		m_p = m_p->next;
	}
	return (1);
}
