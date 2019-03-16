#include "job_control.h"
#include "shell_env.h"
#include "shell_lib.h"


static void insert_process(t_jobs *job, t_process *new)
{
	t_process	*curr;

	curr = job->process;
	if (!curr)
		job->process = new;
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
}

t_process		*create_process(t_execute *exec, t_s_env *e)
{
	t_jobs		*job;
	t_process	*new;

	if (!(new = ft_memalloc(sizeof(t_process))))
		return (NULL);
	job = job_by_id(e->job_id, e->jobs);
	(void)exec;
	insert_process(job, new);
	return (new);
}
