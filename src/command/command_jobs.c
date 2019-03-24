#include "libft.h"
#include "shell_lib.h"
#include "job_control.h"
#include "operator_types.h"


/*void		evaluate_process(t_process *p)
{
	if (p->type == IS_A_PIPE)
}*/

/*static void	check_type(t_process *p)
{
	if (p->type & AND && p->type & PIPED)
		printf(" && and pipe\n");
	else if (p->type & OR && p->type & PIPED)
		printf(" || and pipe\n");
	else if (p->type & PIPED)
		printf("Is a pipe\n");
	else if (p->type & AND)
		printf(" &&\n");
	else if (p->type & OR)
		printf(" OR\n");
	else if (p->type & END_OF_PIPE)
		printf("End of pipe\n");
	else
		printf("Single command\n");
}*/

int			command_job(t_jobs *job, t_s_env *e)
{
	int		ret;

	ret = 0;
	for (t_m_process *m_p = job->m_process; m_p; m_p = m_p->next)
	{
		printf("m_process with process :%p\n", m_p->p);
		for (t_process *p = m_p->p; p; p = p->next)
		{
			printf("{%p} with command [%s]\n", p, ((t_execute *)p->exec)->cmd[0]);
		//	check_type(p);
		/*	if (p->type & PIPED)
				command_pipe(job, p, e, (int[2]){ 0, 0});
			else
				e->ret = command_check(job, p, e);
			break ;
			*/
		//	ret = e->ret;
		//	ret += command_restore_fds(((t_execute *)job->process->exec)->fds);
		}
	}
	(void)e;
	//job_handler(job, e);
	return (0);
}
