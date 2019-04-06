#include "job_control.h"
#include "ft_printf.h"



void		proc_print_status(t_jobs *job, t_process *p, char c)
{
	if (job->pgid == p->pid)
		ft_printf("[%d]\t%c ", job->id, c);
	else
		ft_putstr("   \t  ");
	ft_printf("%d\t", p->pid);

}

void		job_print_status(t_jobs *job)
{
	ft_printf("[%d] %d\n", job->id, job->pgid);
}
