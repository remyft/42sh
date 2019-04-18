/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:08:47 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/18 10:58:10 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "ft_printf.h"
#include <signal.h>

void	job_show_status(t_jobs *job)
{
		ft_printf("[%d]+  %-22s command\n", job->id,
				process_translate_status(job->m_process->p->status));
}

int		job_notify(t_jobs *job)
{
	int		sig;

	sig = job_signaled(job);
	if (sig || (job_suspended(job) && !job_finished(job)))
	{
		if (sig != SIGINT && sig != SIGQUIT && sig != SIGPIPE)
		{
			write(1, "\n", 1);
			job_show_status(job);
		}
	}
	return (sig);
}
