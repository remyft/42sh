/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_foreground.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:36:31 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/23 11:36:40 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "job_control.h"
#include <signal.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include "signal_intern.h"

static int	job_fg_cont(t_jobs *job, t_s_env *e, int cont)
{
	sig_to_pgid(job->pgid);
	job->status |= JOB_FOREGROUND;
	job->status |= JOB_NOTIFIED;
	if (cont)
	{
		job->notify = 1;
		printf("Resume %d\n", job->pgid);
		if (kill(-job->pgid, SIGCONT) < 0)
		{
			ft_dprintf(2, "failed to continue job [%d]\n", job->pgid);
			return (job_kill(job, e));
		}
	}
}

int			job_foreground(t_jobs *job, t_s_env *e, int cont)
{
	int		status;

	job_fg_cont(job, e, cont);
	if (ioctl(e->fd, TIOCSPGRP, &job->pgid) < 0)
	{
		ft_dprintf(2, "job [%d] tcsetpgrp failed\n", job->pgid);
		return (job_kill(job, e));
	}
	status = job_wait(job);
	if (job_finished(job) == 0 && tcgetattr(e->fd, &e->save) != 0)
		dprintf(2, "Error make tcgetattr\n");
	if (ioctl(e->fd, TIOCSPGRP, &e->pid) < 0)
	{
		ft_dprintf(2, "job [%d] tcsetpgrp failed\n", job->pgid);
		return (job_kill(job, e));
	}
	sig_to_pgid(0);
	// RETURN VALUE 128 + sig , if sig > 0 ???
	return (status);
}
