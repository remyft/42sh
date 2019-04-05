#include "shell_env.h"
#include "job_control.h"
#include <stdio.h>

void			command_process(pid_t pid, t_jobs *job, t_process *p)
{
	if (job->pgid == 0)
		job->pgid = pid;
	if (setpgid(p->pid, job->pgid) < 0)
	{
		dprintf(2, "Setpgid failed %s\n", __func__);
		// error
	}
}
