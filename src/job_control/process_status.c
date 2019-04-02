#include "job_control.h"
#include <stdio.h>
#include <errno.h>

int		process_set_status(t_jobs *job, t_process *p, int status)
{
	p->exit_status = WEXITSTATUS(status);
	if (WIFSTOPPED(status))
		p->status = WSTOPSIG(status);
	else
	{
		if (WIFEXITED(status) || WIFSIGNALED(status))
		{
			p->status = STATUS_FINISHED;
			if (WIFSIGNALED(status))
				p->s_signal = WIFSIGNALED(status);
			if (p->s_signal == SIGINT)
				job->status = p->s_signal;
		}
	}
	// maybe things to do;
	return (1);
}

t_process	*process_by_pid(t_m_process *m_p, pid_t pid)
{
	t_process	*p;

	p = m_p->p;
	while (p)
	{
		if (p->pid == pid)
			return (p);
		p = p->next;
	}
	return (NULL);
}

int		process_update(t_jobs *job, t_m_process *m_p, pid_t pid, int status)
{
	t_process	*p;

	if (pid <= 0)
		return (-1);
	if ((p = process_by_pid(m_p, pid)))
	{
		process_set_status(job, p, status);
		m_p->ret = p->exit_status;
		return (0);
	}
	return (-1);
}

void	process_status(t_jobs *job, t_m_process *m_p, t_process *p)
{
	int		status;
	int		errno;
	pid_t	pid;

	errno = 0;
	if (p->status != STATUS_FINISHED
			|| p->status != STATUS_SUSPENDED)
	{
		pid = waitpid(p->pid, &status, WUNTRACED);
		if (pid < 0 && errno == ECHILD)
			p->status = STATUS_FINISHED;
		else
			process_update(job, m_p, pid, status);
	}
}

