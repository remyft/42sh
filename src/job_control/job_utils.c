/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:17:20 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/02 15:44:00 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

int		job_by_pid(t_s_env *e, pid_t pid)
{
	t_jobs	*jobs;

	jobs = e->jobs;
	while (jobs)
	{
		if (jobs->process->pid == pid)
			return (jobs->id);
		jobs = jobs->next;
	}
	return (0);
}

int	job_completed(t_jobs *jobs, int job_id)
{
	while (jobs)
	{
		if (jobs->id == job_id)
			break ;
		jobs = jobs->next;
	}
	if (jobs->process->status == JOB_TERMINATED)
		return (0);
	return (1);
}
