#include "job_control.h"

int		job_wait(t_jobs *job)
{
	t_m_process	*m_p;
	t_process	*p;

	while (1)
	{
		m_p = job->m_process;
		while (m_p)
		{
			p = m_p->p;
			while (p)
			{
				process_status(job, m_p, p);
				p = p->next;
			}
			m_p = m_p->next;
		}
		if (job_finished(job) || job_stopped(job))
			break ;
	}
	return (0);
}
