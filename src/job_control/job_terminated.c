/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_terminated.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:18:47 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/18 18:40:18 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_lib.h"
#include "job_control.h"
#include <errno.h>
#include <stdio.h>

void	free_proc(t_process *proc)
{
	if (proc)
	{
		sh_freetab(&proc->cmd);
	//	free(proc->cmd);
		free_proc(proc->next);
		free(proc);
	}
}

void	remove_job(t_jobs **jobs, int id)
{
	t_jobs		*job;

	job = job_by_id(id, *jobs);
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
	t_jobs	*job;

	while ((pid = waitpid(WAIT_ANY, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
	{
		if (!(job = job_by_pid(e, pid)))
			break ;
	     if (WIFEXITED(status))
			proc_update(e,job, pid, status);
		else if (WIFSTOPPED(status))
			proc_update(e,job, pid, status);
        else if (WIFCONTINUED(status))
			proc_update(e,job, pid, status);
		if (job_completed(job))
		{
			printf("[%d]+ Done [%d]\t\t%s\n", job->id, pid, "Command");
			remove_job(&e->jobs, job->id);
		}
	}
	return (1);
}

int	job_completed(t_jobs *job)
{
	t_process	*proc;

	if (!job)
		return (0);
	proc = job->process;
	while (proc)
	{
		if (proc->status != STATUS_FINISHED)
			return (0);
		proc = proc->next;
	}
	return (1);
}
