#include "job_control.h"
#include <stdio.h>

int		job_finished(t_jobs *job)
{
	t_process	*p;
	t_m_process	*m_p;

	m_p = job->m_process;
	while (m_p)
	{
		p = m_p->p;
		while (p)
		{
			if (p->status != STATUS_FINISHED)
				return (0);
			p = p->next;
		}
		m_p = m_p->next;
	}
	return (1);
}
