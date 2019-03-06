#include "job_control.h"
#include "shell_env.h"


static void insert_process(t_jobs *job, t_process *new)
{

}

t_process		*create_process(t_execute *exec, t_s_env *e)
{
	t_jobs		*job;
	t_process	*new;

	if (!(new = ft_memalloc(sizeof(t_process))))
		return (NULL);
	job = get_job_by_id(e->job_id, e->jobs);
}
