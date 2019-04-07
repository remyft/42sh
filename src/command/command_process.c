#include "shell_env.h"
#include "job_control.h"
#include <stdio.h>

void			command_process(pid_t pid, pid_t s_pid, t_jobs *job, t_process *p)
{
	if (job->pgid == 0 || job->pgid == s_pid)
		job->pgid = pid;
	if (setpgid(p->pid, job->pgid) < 0)
	{
		dprintf(2, "Setpgid failed %s\n", __func__);
		// error
	}
}
