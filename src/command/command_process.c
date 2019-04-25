#include "shell_env.h"
#include "job_control.h"
#include <stdio.h>

void			command_process(pid_t pid, pid_t s_pid, t_jobs *job, t_process *p)
{
	p->status = STATUS_RUNNING;
	if (job->pgid == 0 || job->pgid == s_pid)
		job->pgid = pid;
	//printf("p->pid : %d job->pgid: %d\n", p->pid, job->pgid);
	if (setpgid(p->pid, job->pgid) < 0)
	{
		dprintf(2, "Setpgid failed %s\n", __func__);
		// error
	}
}
