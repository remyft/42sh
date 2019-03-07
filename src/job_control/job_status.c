/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:39:27 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/06 16:13:55 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void		get_job_status(t_jobs *jobs)
{
	int		status;
	int		id;
	pid_t	pid;

	while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
	{
		// see later for return value of process
		if (WIFEXITED(status))
			// status
			;
		else if (WIFSTOPPED(status))
			// status
			;
		else if (WIFCONTINUED(status))
			// need to set status
			;
		//id = get_job_id(pid);
	//	if (id && job_end(id))
			//end_job(id);
		(void)jobs;
		(void)id;
	}
}
