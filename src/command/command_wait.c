/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 20:23:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/18 17:50:27 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_env.h"
#include <sys/wait.h>
#include "command.h"
#include "job_control.h"

int		command_job_wait(t_jobs *job, t_m_process *m_p, t_s_env *e)
{
	int		status;

	if (!e->interactive)
	{
		e->async = 0;
		job_wait(job, m_p);
	}
	else if (e->async)
		return (job_background(job, m_p));
	else
		if ((status = job_foreground(job, e, m_p, 0)) != 0)
			return (status);
	return (1);
}
