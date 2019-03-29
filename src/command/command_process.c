#include "shell_env.h"
#include "job_control.h"

void			command_process(pid_t pid, t_jobs *job, t_process *p, t_s_env *e)
{
	if (e->interactive)
	{
		if (!job->pgid)
			job->pgid = pid;
		setpgid(p->pid, job->pgid);
	}
}
