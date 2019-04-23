/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:38:57 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/23 11:39:12 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "ft_printf.h"
#include <signal.h>

int		job_background(t_jobs *job, t_s_env *e, int cont)
{
	if (cont == 1)
	{
		job->foreground = 1;
		if (kill(-job->pgid, SIGCONT) < 0)
			return (job_kill(job, e));
	}
	if (job->prev)
	{
		job->status |= JOB_LAST;
		job->prev->status &= ~JOB_LAST;
		job->prev->status |= JOB_MINUS;
		if (job->prev->prev)
			job->prev->prev->status &= ~JOB_MINUS;
	}
	else
		job->status |= JOB_LAST;
	if (job->notify == 0)
		ft_printf("[%d] %d\n", job->id, job->pgid);
	return (0);
}
