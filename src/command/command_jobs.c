#include "libft.h"
#include "shell_lib.h"
#include "job_control.h"
#include "command.h"
#include "operator_types.h"
#include "command_error.h"
#include <stdio.h>

static void	set_fds(int *fds, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		fds[i] = -1;
}

static int launch_m_process(t_jobs *job, t_m_process *m_p, t_s_env *e)
{
	int			fds[5];
	int			ret;
	t_process	*curr;

	set_fds(fds, 5);
	curr = m_p->p;
	job->pgid = 0;
	while (curr)
	{
		if ((ret = command_pipe_dup(job, curr, e, fds)) != 0)
		{
			close_unexpected_fd(fds);
			fds[FD_STDIN] = fds[FD_PIPE_IN];
			return (ret);
		}
		close_unexpected_fd(fds);
		fds[FD_STDIN] = fds[FD_PIPE_IN];
		m_p->ret = curr->exit_status;
		curr = curr->next;
	}
	return (0);
}

#include "job_control.h"

int		command_test_wait(t_jobs *job, t_m_process *m_p, t_s_env *e)
{
	(void)e;
	(void)m_p;
	return (job_wait(job));
}

int		command_launch_mp_b(t_jobs *job, t_s_env *e)
{
	int		ret;

	ret = 0;
	for (t_m_process *m_p = job->m_process; m_p; m_p = m_p->next)
	{
		if (m_p->type == OR_IF_VALUE && !ret)
			continue ;
		if ((ret = launch_m_process(job, m_p, e)) != 0)
			return (ret);
		job->notify = 1;
	//	if ((ret = command_job_wait(job, e)) != 0)
		if ((ret = command_test_wait(job, m_p, e)) != 0)
		{
			command_restore_fds(((t_execute *)m_p->p->exec)->fds);
			return (ret);
		}
		ret = m_p->ret;
		command_restore_fds(((t_execute *)m_p->p->exec)->fds);
	}
	//jobs_notify_ended(e->jobs);
	return (0);
}

int		command_mprocess_background(t_jobs *job, t_s_env *e)
{
	int			error;

	error = 0;
	if ((job->pgid = fork()) == 0)
	{
		error = command_launch_mp_b(job, e);
		exit(EXIT_FAILURE);
	}
	else if (job->pgid < 0)
		error = command_error(e->progname, ERR_FORK, NULL, e);
	command_job_wait(job, e);
	job->status |= JOB_FORKED;
	return (error);
}

int			command_job(t_jobs *job, t_s_env *e)
{
	int		ret;

	ret = 0;
	if (job->m_process->next && job->foreground == 1)
		return (command_mprocess_background(job, e));
	for (t_m_process *m_p = job->m_process; m_p; m_p = m_p->next)
	{
		if (m_p->type == OR_IF_VALUE && !ret)
			continue ;
		if ((ret = launch_m_process(job, m_p, e)) != 0)
			return (ret);
		if ((ret = command_job_wait(job, e)) != 0)
		{
			command_restore_fds(((t_execute *)m_p->p->exec)->fds);
			return (ret);
		}
		ret = m_p->ret;
		command_restore_fds(((t_execute *)m_p->p->exec)->fds);
	}
	return (0);
}
