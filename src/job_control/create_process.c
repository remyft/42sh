#include "job_control.h"
#include "shell_env.h"
#include "shell_lib.h"


static void insert_process(t_jobs *job, t_process *new)
{
	t_m_process	*m_p;
	t_process	*curr;

	m_p = job->curr;
	curr = m_p->p;
	if (!curr)
		m_p->p = new;
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
}

int		create_process(t_s_env *e, t_execute *exec, int type)
{
	t_jobs		*job;
	t_process	*new;

	if (!(new = ft_memalloc(sizeof(t_process))))
		return (0);
	new->exec = exec;
	new->type = type;
	job = job_by_id(e->job_id, e->jobs);
	insert_process(job, new);
	return (1);
}
