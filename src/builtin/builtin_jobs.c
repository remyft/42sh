#include "shell_env.h"
#include "ft_dprintf.h"
#include "ft_printf.h"
#include "job_control.h"

static void	print_opt_error(char *s)
{
	ft_dprintf(2, "42sh: jobs: %.2s: invalid option\n", s);
}

static void	print_opt_p(t_jobs *jobs, t_execute *exec)
{
	while (jobs)
	{
		if ((t_execute *)jobs->m_process->p->exec == exec)
			;
		else
			ft_printf("%d\n", jobs->pgid);
		jobs = jobs->next;
	}
}

int		print_jobs(t_jobs *jobs, t_execute *exec, t_s_env *e)
{
	int		i;

	i = 1;
	(void)e;
	while (exec->cmd[i] && exec->cmd[i][0] == '-')
	{
		if (ft_strequ(exec->cmd[i], "--help"))
			ft_printf("--help\n");
	//		print_help();
		else if (!ft_strcmp(exec->cmd[i], "-l"))
			ft_printf("-l\n");
		else if (!ft_strcmp(exec->cmd[i], "-p"))
			print_opt_p(jobs, exec);
		else
		{
			ft_printf("enter\n");
			print_opt_error(exec->cmd[i]);
		}
		i++;
	}
	return (1);
}

int		builtin_jobs(t_execute *exec, t_s_env *e)
{
	print_jobs(e->jobs, exec, e);
	return (0);
}
