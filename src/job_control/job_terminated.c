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
#include <signal.h>
#include <stdio.h>

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
	free_proc(job->m_process->p);
	free(job);
}

/*static void	ended(int jobs)
{
	(void)jobs;
	printf("Ended\n");
}*/

int	jobs_terminated(t_s_env *e)
{
	int		status;
	t_jobs	*jobs;
	pid_t	pid;

	signal(SIGCHLD, SIG_DFL);
	while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
	{
		jobs = job_by_pid(e, pid);
	    if (WIFEXITED(status))
			proc_update(e, 0, pid, status);
		else if (WIFSTOPPED(status))
			proc_update(e, 0, pid, status);
        else if (WIFCONTINUED(status))
			proc_update(e, 0, pid, status);
		if (job_completed(jobs))
		{
			printf("[%d]+ Done [%d]\t\t%s\n", jobs->id, pid, "Command");
	//		remove_job(&e->jobs, job->id);
		}
	}
	return (1);
}

int	job_completed(t_jobs *job)
{
	t_process	*proc;

	if (!job)
		return (0);
	proc = job->m_process->p;
	while (proc)
	{
		if (proc->status != STATUS_FINISHED)
			return (0);
		proc = proc->next;
	}
	return (1);
}
