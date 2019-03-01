/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 21:33:49 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/01 17:13:25 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_insert.h"
#include <stdio.h>

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

void	add_job(t_jobs *jobs, t_jobs *new)
{
	size_t		id;

	id = 2;
	if (jobs == NULL || new == NULL)
		return ;
	while (jobs->next)
	{
		id++;
		jobs = jobs->next;
	}
	new->id = id;
	jobs->next = new;
}

int		job_insert(t_s_env *e, char **cmd)
{
	t_jobs		*job;
	int			id;

	id = 1;
	job = NULL;
	if (!(job = ft_memalloc(sizeof(t_jobs))))
		return (0);
	job->pgid = -1;
	job->id = 1;
	if (!(job->process = ft_memalloc(sizeof(t_process))))
		return (0);
	job->process->pid = -1;
	job->process->cmd = ft_strdup(cmd[0]);
	if (!e->jobs)
		e->jobs = job;
	else
		add_job(e->jobs, job);
	return (job->id);
}

