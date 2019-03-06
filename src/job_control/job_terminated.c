/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_terminated.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:18:47 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/06 11:49:23 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_lib.h"
#include "job_control.h"
#include <stdio.h>

void	free_proc(t_process *proc)
{
	if (proc)
	{
	//	sh_freetab(&proc->cmd);
		free(proc->cmd);
		free_proc(proc->next);
		free(proc);
	}
}

void	remove_job(t_jobs **jobs, int id)
{
	t_jobs		*job;

	job = get_job_by_id(id, *jobs);
	if (*jobs == job)
		*jobs = job->next;
	if (job->next != NULL)
		job->next->prev = job->prev;
	if (job->prev != NULL)
		job->prev->next = job->next;
	free_proc(job->process);
	free(job);
}

int	jobs_terminated(t_s_env *e)
{
	int		status;
	pid_t	pid;
	int		job_id;

	while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
	{
		job_id = job_by_pid(e, pid);
		if (job_id > 0 && job_completed(e->jobs, job_id))
		{
			printf("[%d]+ Done [%d]\t\t%s\n", job_id, pid, "Command");
			remove_job(&e->jobs, job_id);
			return (1);
		}
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
