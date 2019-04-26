/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 09:43:12 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/25 23:02:58 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_env.h"
#include "job_control.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "command.h"
#include <stdio.h>

int		command_ret(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status) + 128);
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

int		command_job_wait(t_jobs *job, t_s_env *e)
{
	int		status;

	if (!e->interactive)
	{
		job->foreground = 0;
		job_wait(job, e);
	}
	//else if (job->status & JOB_FORKED)
		//return (job_wait(job));
	else if (job->status & JOB_BUILTIN_INTERN)
	{
		job->status &= ~JOB_BUILTIN_INTERN;
		return (0);
	}
	else if (job->foreground == 1)
		return (job_background(job, e, 0));
	else
	{
		if ((status = job_foreground(job, e, 0)) != 0)
			return (status);
	}
	return (0);
}
