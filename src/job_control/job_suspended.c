/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_suspended.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:40:39 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/03 18:41:16 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <stdio.h>

int		job_suspended(t_jobs *job)
{
	t_process	*p;
	t_m_process	*m_p;

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
