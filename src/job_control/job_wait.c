/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:33:20 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/24 18:06:25 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <stdio.h>

int		job_wait(t_jobs *job, t_s_env *e)
{
	t_m_process	*m_p;
	t_process	*p;

	while (1)
	{
		m_p = job->m_process;
		while (m_p)
		{
			p = m_p->p;
			while (p)
			{
				process_status(job, m_p, p, e);
				p = p->next;
			}
			if (job_suspended(job, m_p))
				return (job_notify(job, m_p));
			m_p = m_p->next;
		}
		if (job_finished(job))
			return (job_notify(job, job->m_process));
	}
}
