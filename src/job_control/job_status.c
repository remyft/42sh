/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:39:27 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/18 18:49:22 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static void	job_wait(t_jobs *job, t_s_env *e)
{
	(void)e;
	int		status;
	pid_t	pid;

	//jobs_terminated(e);
	do 
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		printf("???\n");
	}
	while (!proc_update(e, job, pid, status)
			&& !job_completed(job));
	//	pid = waitpid(WAIT_ANY, &status, WUNTRACED);

}

static void	job_foreground(t_jobs *job, t_s_env *e)
{
	tcsetpgrp(0, job->pgid);
	job_wait(job, e);
	tcsetpgrp(0, e->pgid);
	
}

static void	job_background(t_jobs *job, t_s_env *e)
{
	(void)e;
	printf("[%d] %d\n", job->id, job->pgid);
}

void		job_handler(t_jobs *job, t_s_env *e)
{
	if (!e->interactive)
		job_wait(job, e);
	else if (!e->async)
		job_foreground(job, e);
	else
		job_background(job, e);

}
