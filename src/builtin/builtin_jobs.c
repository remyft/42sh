#include "shell_env.h"
#include "ft_dprintf.h"
#include "job_control.h"

int		builtin_jobs(t_execute *exec, t_s_env *e)
{
	t_jobs		*jobs;

	jobs = e->jobs;
	(void)exec;
	/*while (jobs->next)
	{
		ft_dprintf(STDOUT_FILENO, "[%d]", jobs->id);
		if (get_status(jobs->process))
			ft_dprintf(STDOUT_FILENO, "  %.8s", STR_FINISHED);
		else
			ft_dprintf(STDOUT_FILENO, "  %.8s", STR_RUNNING);
		ft_dprintf(STDOUT_FILENO, "\t%s\n", ((t_execute *)jobs->process->exec)->cmd[0]);
		jobs = jobs->next;
	}*/
	return (0);
}
