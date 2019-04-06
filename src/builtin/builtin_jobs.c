#include "shell_env.h"
#include "ft_dprintf.h"
#include "job_control.h"

int		builtin_jobs(t_execute *exec, t_s_env *e)
{
	t_jobs		*jobs;
	t_jobs		*head;

	jobs = e->jobs;
	head = jobs;
	(void)exec;
	while (jobs && jobs->next && jobs->next->next != head)
	//while (jobs && jobs->next != head)
	{
		printf("job [%d] with pid : %d\n", jobs->id, jobs->pgid);
		jobs = jobs->next;
	}
	return (0);
}
