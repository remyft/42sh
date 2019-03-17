/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_terminated.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:18:47 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/10 18:28:46 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_lib.h"
#include "job_control.h"
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

	while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
	{
		if (!(job = job_by_pid(e, pid)))
			break ;
 //       if (WIFEXITED(status))
	//		set_pstatus(job->process, pid, STATUS_FINISHED);
	/*	else if (WIFSTOPPED(status))
			set_pstatus(job->process, pid, STATUS_SUSPENDED);
        else if (WIFCONTINUED(status))
            set_pstatus(job->process, pid, STATUS_CONTINUED);
			*/
	//	printf("Getting pid :%d with job [%d]\n", pid, job_id);
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
