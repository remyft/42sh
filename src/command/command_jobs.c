#include "libft.h"
#include "shell_lib.h"
#include "job_control.h"
#include "command.h"
#include "operator_types.h"
#include <stdio.h>

static void	set_fds(int *fds, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		fds[i] = -1;
}

static void	launch_m_process(t_jobs *job, t_m_process *m_p, t_s_env *e)
{
	int			fds[5];
	t_process	*curr;

	set_fds(fds, 5);
	curr = m_p->p;
	while (curr)
	{
		command_pipe_dup(job, curr, e, fds);
		close_unexpected_fd(fds);
		fds[FD_STDIN] = fds[FD_PIPE_IN];
		m_p->ret = curr->exit_status;
		curr = curr->next;
	}
}

int			command_job(t_jobs *job, t_s_env *e)
{
	int		ret;

	ret = 0;
	for (t_m_process *m_p = job->m_process; m_p; m_p = m_p->next)
	{
		if (m_p->type == OR_IF_VALUE && !ret)
			continue ;
		launch_m_process(job, m_p, e);
		if ((ret = command_job_wait(job, e)) != 0)
		{
			command_restore_fds(((t_execute *)m_p->p->exec)->fds);
			return (ret);
		}
		ret = m_p->ret;
		command_restore_fds(((t_execute *)m_p->p->exec)->fds);
	}
	//if (e->async == 0)
		//remove_job(&e->jobs, job->id);
	return (0);
}
