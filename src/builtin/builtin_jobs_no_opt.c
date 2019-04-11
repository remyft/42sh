/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs_no_opt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:35:49 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/11 17:42:51 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "builtin_jobs.h"
#include "ft_printf.h"

int		jobs_evaluate_status(t_m_process *m_p)
{
	t_process	*p;

	while (m_p)
	{
		p = m_p->p;
		while (p)
		{
			if (p->status != STATUS_FINISHED)
				return (p->status);
			p = p->next;
		}
		m_p = m_p->next;
	}
	return (STATUS_FINISHED);
}

void	job_no_opt(const t_jobs *curr)
{
	int		status;

	ft_printf("[%d]", curr->id);
	if (curr->status & JOB_LAST)
		ft_printf("+  ");
	else if (curr->status & JOB_MINUS)
		ft_printf("-  ");
	else
		ft_printf("   ");
	if ((status = jobs_evaluate_status(curr->m_process)))
		ft_printf("%-22\n", process_translate_status(status));
	ft_printf("\n");
}
