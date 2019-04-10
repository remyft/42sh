/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 20:23:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/10 16:43:11 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_env.h"
#include "command.h"
#include "job_control.h"
#include <signal.h>
#include <stdio.h>

int		command_job_wait(t_jobs *job, t_s_env *e)
{
	int		status;

	if (!e->interactive)
	{
		job->foreground = 0;
		job_wait(job);
	}
	else if (job->status & JOB_BUILTIN_INTERN)
		return (0);
	else if (job->foreground == 1)
		return (job_background(job, e, 0));
	else
		if ((status = job_foreground(job, e, 0)) != 0)
			return (status);
	return (0);
}
