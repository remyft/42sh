#include "job_control.h"
#include "ft_printf.h"


void		proc_translate_status(int status)
{
	if (status == STATUS_FINISHED)
		ft_printf("%s\t\n", STR_TERMINATED);
	if (status == STATUS_RUNNING)
		ft_printf("%s\t\n", STR_RUNNING);
	if (status == STATUS_SUSPENDED)
		ft_printf("%s\t\n", STR_SUSPENDED);
}

void		proc_print_status(t_jobs *job, t_process *p, char c)
{
	if (job->pgid == p->pid)
		ft_printf("[%d]\t%c ", job->id, c);
	else
		ft_putstr("   \t  ");
	ft_printf("%d\t", p->pid);
	proc_translate_status(p->status);

}

void		job_print_status(t_jobs *job)
{
	ft_printf("[%d] %d\n", job->id, job->pgid);
}
