/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:17:32 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/09 16:18:03 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void	free_proc(t_process *proc)
{
	if (proc)
	{
		command_free((t_execute *)proc->exec, NULL);
		proc->exec = NULL;
		free_proc(proc->next);
		free(proc);
	}
}

void	remove_job(t_jobs **job, t_jobs *node)
{
	if (*job == NULL || node == NULL)
		return ;
	if (*job == node)
		*job = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	free_proc(node->m_process->p);
	free(node->m_process);
	free(node);
	node = NULL;
}

#include <stdio.h>

void	jobs_remove(t_jobs **jobs, int n)
{
	t_jobs	*curr;
	t_jobs	*save;

	if (!jobs || !*jobs)
		return ;
	curr = *jobs;
	while (curr)
	{
		save = curr->prev;
		if (n == 0 || (curr->status & JOB_NOTIFIED))
		{
			printf("Removing jobs %d\n", curr->id);
			remove_job(jobs, curr);
			curr = save;
		}
		else
			curr = curr->next;
	}
}
