#include "job_control.h"
#include "ft_dprintf.h"
#include <signal.h>
#include <sys/ioctl.h>

int		job_kill(t_jobs *job, t_s_env *e)
{
	if (job->pgid != 0)
	{
		kill(-job->pgid, SIGTERM);
		kill(-job->pgid, SIGCONT);
	}
	//job->notified = 1;
	if (ioctl(e->fd, TIOCSPGRP, &job->pgid) < 0)
	{
		ft_dprintf(2, "job [%d] tcsetpgrp failed\n", job->pgid);
		return (1);
	}
	return (0);
}
