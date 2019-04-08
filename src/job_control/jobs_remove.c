/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:17:32 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/08 16:09:28 by dbaffier         ###   ########.fr       */
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

void	remove_job(t_jobs **job)
{
	if ((*job)->next != NULL)
		(*job)->next->prev = (*job)->prev;
	if ((*job)->prev != NULL)
		(*job)->prev->next = (*job)->next;
	free_proc((*job)->m_process->p);
	free((*job)->m_process);
	free(*job);
	*job = NULL;
}

#include <stdio.h>

void	jobs_remove(t_jobs **jobs, int n)
{
	t_jobs	*curr;
	t_jobs	*save;

	if (!jobs || !*jobs)
		return ;
	save = (*jobs)->next;
	if (save == NULL)
	{
		if (n == 0 || ((*jobs)->status & JOB_NOTIFIED))
		{
			printf("Removing job %d\n", (*jobs)->id);
			remove_job(jobs);
		}
	}
	else
	{
		while ((curr = save) && curr != *jobs)
		{
			save = save->next;
			if (n == 0 || curr->status & JOB_NOTIFIED)
			{
				printf("Removing job %d\n", curr->id);
				remove_job(&curr);
			}
		}
	}
}
