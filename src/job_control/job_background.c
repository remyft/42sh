#include "job_control.h"
#include <signal.h>

int		job_background(t_jobs *job, t_s_env *e, int cont)
{
	if (cont == 1)
		if (kill(-job->pgid, SIGCONT) < 0)
			return (job_kill(job, e));
	job_print_status(job);
	(void)cont;
	(void)job;
	return (0);
}
