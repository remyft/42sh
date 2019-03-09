/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:17:20 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/07 17:44:42 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_jobs		*get_job_by_id(int id, t_jobs *jobs)
{
	while (jobs)
	{
		if (jobs->id == id)
			return (jobs);
		jobs = jobs->next;
	}
	return (jobs);
}

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

