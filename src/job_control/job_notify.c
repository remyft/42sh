/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:08:47 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/11 17:30:45 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "ft_printf.h"
#include <signal.h>

char	*process_translate_status(int status)
{
	if (status == STATUS_FINISHED)
		return (STR_TERMINATED);
	if (status == STATUS_RUNNING)
		return (STR_RUNNING);
	if (status == STATUS_SUSPENDED)
		return (STR_SUSPENDED);
	if (status == STATUS_STOPPED)
		return (STR_STOPPED);
	return (STR_RUNNING);
}

void	job_show_status(t_jobs *job)
{
		ft_printf("\n[%d]+  %-22s command\n", job->id,
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
	return (1);
}
