/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:08:47 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/23 08:43:24 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "ft_printf.h"
#include "signal_intern.h"

void	job_show_status(t_jobs *job, int sig)
{
	printf("There\n");
	if (sig > 0)
		ft_printf("%s: %d\n", sig_err_translate(sig), sig);
	else
		ft_printf("[%d]+  %-22s command\n", job->id,
			process_translate_status(job->m_process->p->status));
}

int		job_notify(t_jobs *job, t_m_process *m_p)
{
	int		sig;
	int		s_suspended;

	if (job->notify == 1)
		return (0);
	sig = 0;
	if ((s_suspended = job_sig_suspended(job, m_p)) > 0)
	{
		write(1, "\n", 1);
		job_show_status(job, sig);
		return (s_suspended);
	}
	else
	{
		sig = job_signaled(job);
		if (sig || (job_suspended(job, m_p) && !job_finished(job)))
		{
			if (sig != SIGINT && sig != SIGQUIT && sig != SIGPIPE)
				job_show_status(job, sig);
		}
		return (sig);
	}
}
