#include "job_control.h"
#include <stdio.h>

int		job_finished(t_jobs *job, t_m_process *m_p)
{
	t_process *p;

	(void)job;
	p = m_p->p;
	while (p)
	{
		if (p->status != STATUS_FINISHED)
			return (0);
		p = p->next;
	}
	return (1);
}
