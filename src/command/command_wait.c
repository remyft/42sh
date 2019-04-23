/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 09:43:12 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/23 11:14:35 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_env.h"
#include "job_control.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "command.h"
#include <stdio.h>

int		command_job_wait(t_jobs *job, t_s_env *e)
{
	int		status;

	if (!e->interactive)
	{
		job->foreground = 0;
		job_wait(job);
	}
	//else if (job->status & JOB_FORKED)
		//return (job_wait(job));
	else if (job->status & JOB_BUILTIN_INTERN)
		return (0);
	else if (job->foreground == 1)
		return (job_background(job, e, 0));
	else
		if ((status = job_foreground(job, e, 0)) != 0)
			return (status);
	return (0);
	//else if (WIFSTOPPED(*ret))
		//*ret = WTERMSIG(*ret) + 128;
}

/*void			command_wait(pid_t pid, int async, int *ret)
{
	pid_t		got;

	if (!async)
		while ((got = waitpid(pid, ret, 0)) > 0)
			if (got == pid)
			{
				command_ret(ret);
				return ;
			}
}*/
