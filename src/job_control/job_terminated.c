/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_terminated.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:18:47 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/02 16:04:57 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <stdio.h>

int	jobs_terminated(t_s_env *e)
{
	int		status;
	pid_t	pid;
	int		job_id;

	while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
	{
		job_id = job_by_pid(e, pid);
		if (job_id > 0 && job_completed(e->jobs, job_id))
		{
			printf("[%d]+ Done [%d]\t\t%s\n", job_id, pid, "Command");
			// remove job
			return (1);
		}
	}
	return (0);
}
