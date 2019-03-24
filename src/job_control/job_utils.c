/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:17:20 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/09 10:10:49 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_jobs		*job_by_id(int id, t_jobs *jobs)
{
	while (jobs)
	{
		if (jobs->id == id)
			return (jobs);
		jobs = jobs->next;
	}
	return (jobs);
}

t_jobs		*job_by_pid(t_s_env *e, pid_t pid)
{
	t_jobs		*jobs;
	t_process	*curr;

	jobs = e->jobs;
	while (jobs)
	{
		curr = jobs->m_process->p;
		while (curr)
		{
			if (curr->pid == pid)
				return (jobs);
			curr = curr->next;
		}
		jobs = jobs->next;
	}
	return (NULL);
}

