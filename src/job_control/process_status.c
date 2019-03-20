#include "job_control.h"

int		set_pstatus(t_process *p, int status)
{
	p->status = status;
	if (WIFEXITED(status))
		p->status = STATUS_FINISHED;
	else if (WIFSIGNALED(status))
		p->status = STATUS_TERMINATED;
	else if (WSTOPSIG(status))
		p->status = STATUS_SUSPENDED;
	return (1);
}

int		proc_update(t_s_env *e, t_jobs *job, pid_t pid, int status)
{
	(void)job;
	if (pid > 0)
	{
		for (t_jobs *jobs = e->jobs; jobs; jobs = jobs->next)
		{
			for (t_process *p = jobs->process; p; p = p->next)
			{
				if (p->pid == pid)
				{
					set_pstatus(p, status);
					return (0);
				}
			}
		}
	}
	return (-1);
}
