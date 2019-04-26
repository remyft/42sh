/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_finished.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:38:04 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/25 17:37:57 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <stdio.h>

static int	job_forked_finished(t_jobs *job)
{
	t_process	*p;

	p = (t_process *)job->job_forked;
	return (p->status != STATUS_FINISHED ? 0 : 1);
}

int			job_finished(t_jobs *job)
{
	t_process	*p;
	t_m_process	*m_p;

	if (job->status & JOB_FORKED)
		return (job_forked_finished(job));
	m_p = job->m_process;
	while (m_p)
	{
		p = m_p->p;
		while (p)
		{
			if (p->status != STATUS_FINISHED)
				return (0);
			p = p->next;
		}
		m_p = m_p->next;
	}
	return (1);
}
