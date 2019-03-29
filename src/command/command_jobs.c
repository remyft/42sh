#include "libft.h"
#include "shell_lib.h"
#include "job_control.h"
#include "command.h"
#include "operator_types.h"

int			command_job(t_jobs *job, t_s_env *e)
{
	int		ret;
	int		fds[5];

	ret = 0;
	for (t_m_process *m_p = job->m_process; m_p; m_p = m_p->next)
	{
		for (t_process *p = m_p->p; p; p = p->next)
		{
			command_pipe_dup(job, p, e, fds);
			close_unexpected_fd(fds);
			fds[FD_STDIN] = fds[FD_PIPE_IN];
		}
		m_p->ret = command_job_wait(job, m_p, e);
		command_restore_fds(((t_execute *)m_p->p->exec)->fds);
	}
	return (0);
}
