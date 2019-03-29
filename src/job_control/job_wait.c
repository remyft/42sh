#include "job_control.h"

int		job_wait(t_jobs *job, t_m_process *m_p)
{
	t_process *p;

	while (1)
	{
		p = m_p->p;
		while (p)
		{
			process_status(job, m_p, p);
			p = p->next;
		}
		if (job_finished(job, m_p))
				//|| job_stopped(job))
			break ;
	}
	return (0);
}
