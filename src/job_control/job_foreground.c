#include "libft.h"
#include "ft_dprintf.h"
#include "job_control.h"
#include <signal.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include "signal_intern.h"

int		job_foreground(t_jobs *job, t_s_env *e, int cont)
{
	sig_to_pgid(job->pgid);
	printf("Enter\n");
	job->status |= JOB_FOREGROUND;
	job->status |= JOB_NOTIFIED;
	if (cont)
	{
		if (kill(-job->pgid, SIGCONT) < 0)
		{
			ft_dprintf(2, "failed to continue job [%d]\n", job->pgid);
			return (job_kill(job, e));
		}
	}
	if (ioctl(e->fd, TIOCSPGRP, &job->pgid) < 0)
	{
		ft_dprintf(2, "job [%d] tcsetpgrp failed\n", job->pgid);
		return (job_kill(job, e));
	}
	job_wait(job);
	if (job_finished(job) == 0 && tcgetattr(e->fd, &e->save) != 0)
		dprintf(2, "Error make tcgetattr\n");
	if (ioctl(e->fd, TIOCSPGRP, &e->pid) < 0)
	{
		ft_dprintf(2, "job [%d] tcsetpgrp failed\n", job->pgid);
		return (job_kill(job, e));
	}
	sig_to_pgid(0);
	return (0);
}
