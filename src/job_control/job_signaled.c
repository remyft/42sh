/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_signaled.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:10:02 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/03 16:12:47 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

int		job_signaled(t_jobs *job)
{
	t_process	*p;
	t_m_process	*m_p;

	m_p = job->m_process;
	while (m_p)
	{
		p = m_p->p;
		while (p)
		{
			if (p->s_signal > 0)
				return (p->s_signal);
			p = p->next;
		}
		m_p = m_p->next;
	}
	return (0);
}
