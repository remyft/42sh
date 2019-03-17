#include "job_control.h"

int		set_pstatus(t_process *p, int status)
{
	p->status = status;
	if (WIFSTOPPED(status))
		p->status = STATUS_FINISHED;
	else if (WIFSIGNALED(status))
		p->status = STATUS_TERMINATED;
	else if (WSTOPSIG(status))
		p->status = STATUS_SUSPENDED;
	return (1);
}

int		proc_update(t_jobs *job, pid_t pid, int status)
{
	t_process	*p;

	p = job->process;
	while (p)
	{
		if (p->pid == pid)
		{
			set_pstatus(p, status);
			return (0);
		}
		p = p->next;
	}
	return (-1);
}
