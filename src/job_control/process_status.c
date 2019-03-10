#include "job_control.h"

int		set_pstatus(t_process *proc, pid_t pid, int status)
{
	while (proc)
	{
		if (proc->pid == pid)
			return (proc->status = status);
		proc = proc->next;
	}
	return (proc->status);
}
