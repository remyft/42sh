#include "job_control.h"
#include "ft_printf.h"
#include <signal.h>

int		job_background(t_jobs *job, t_s_env *e, int cont)
{
	if (cont == 1)
		if (kill(-job->pgid, SIGCONT) < 0)
			return (job_kill(job, e));
	ft_printf("[%d] %d\n", job->id, job->pgid);
	(void)cont;
	(void)job;
	return (0);
}
