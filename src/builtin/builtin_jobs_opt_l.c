/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs_opt_l.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:19:44 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/11 16:09:32 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "ft_printf.h"
#include "builtin_jobs.h"
#include "signal_intern.h"
void	job_opt_l_print(const t_jobs *job, const t_process *p)
{
	ft_printf("[%d]", job->id);
	if (job->status & JOB_LAST)
		ft_printf("+  ");
	else if (job->status & JOB_MINUS)
		ft_printf("-  ");
	else
		ft_printf("   ");
	ft_printf("%d ", p->pid);
	if (p->status == STATUS_STOPPED)
	{
		if (p->s_suspended == 17 || p->s_suspended == 18)
			ft_printf("%s %d ", STR_SUSPENDED, p->s_suspended);
		else
			ft_printf("%s: %d ", sig_err_translate(p->s_suspended), p->s_suspended);
	}
	else
	{
		if (p->s_signal > 0)
			ft_printf("%-24s", sig_err_translate(p->s_signal));
		else
			ft_printf("%-24s", process_translate_status(p->status));
	}
	ft_printf("%s", job->cmd_name);
	ft_printf("\n");
}

void	job_opt_l(const t_jobs *job)
{
	t_process	*p;

	job_opt_l_print(job, job->m_process->p);
	if (job->m_process->next)
		return ;
	p = job->m_process->p->next;
	while (p)
	{
		ft_printf("      ");
		ft_printf("%d ", p->pid);
		if (p->status == STATUS_STOPPED)
		{
			if (p->s_suspended == 17 || p->s_suspended == 18)
				ft_printf("%s %-24d", STR_SUSPENDED, p->s_suspended);
			else
				ft_printf("%s %s, %-24d", STR_STOPPED, sig_err_translate(p->s_suspended), p->s_suspended);
		}
		else
		{
			if (p->s_signal > 0)
				ft_printf("%-24s", sig_err_translate(p->s_signal));
			else
				ft_printf("%-24s", process_translate_status(p->status));
		}
		ft_printf("%s", job->cmd_name);
		ft_printf("\n");
		p = p ->next;
	}
}
