#include "libft.h"
#include "shell_lib.h"
#include "job_control.h"
#include "operator_types.h"


/*void		evaluate_process(t_process *p)
{
	if (p->type == IS_A_PIPE)
}*/

static void	check_type(t_process *p)
{
	if (p->type & IS_A_PIPE && p->type & AND_IF_VALUE)
		printf("Is a pipe and && \n");
	else if (p->type & IS_A_PIPE)
		printf("Is a pipe\n");
	else
		printf("End of pipe\n");
}

int			command_job(t_jobs *job, t_s_env *e)
{
	int		ret;

	ret = 0;
	for (t_process *p = job->process; p; p = p->next)
	{
		printf("{%p} with command [%s]\n", p, ((t_execute *)p->exec)->cmd[0]);
		check_type(p);
	//	e->ret = command_check(job, p, e);
	//	ret = e->ret;
	//	ret += command_restore_fds(((t_execute *)job->process->exec)->fds);
	}
	job_handler(job, e);
	return (0);
}
