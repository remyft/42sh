/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 21:33:49 by dbaffier          #+#    #+#             */
/*   Updated: 2019/02/26 22:27:57 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_insert.h"
#include <stdio.h>

int		insert_job(t_s_env *e)
{
	t_jobs		*job;
	t_jobs		*curr;
	int			id;

	id = 1;
	(void)e;
	job = NULL;
	curr = NULL;
	/*curr = e->jobs;
	if (!(job = ft_memalloc(sizeof(t_jobs))))
		return (0);
	job->pgid = -1;
	while (curr)
	{
		id++;
		curr = curr->next;
	}
	job->id = id;
	curr->next = job;
	*/
	printf("hi\n");
	return (1);
}

