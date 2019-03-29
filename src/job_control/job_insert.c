/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 21:33:49 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/29 15:56:05 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void	add_job(t_jobs *jobs, t_jobs *new)
{
	if (jobs == NULL || new == NULL)
		return ;
	while (jobs->next)
		jobs = jobs->next;
	new->id = jobs->id + 1;
	jobs->next = new;
	new->prev = jobs;
}

t_jobs	*job_insert(t_s_env *e)
{

	t_jobs		*job;
	int			id;

	id = 1;
	job = NULL;
	if (!(job = ft_memalloc(sizeof(t_jobs))))
		return (0);
	job->id = 1;
	if (!e->jobs)
		e->jobs = job;
	else
		add_job(e->jobs, job);
	e->job_id = job->id;
	return (job);
}

