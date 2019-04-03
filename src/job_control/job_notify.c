/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:08:47 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/03 18:42:49 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <signal.h>

int		job_notify(t_jobs *job)
{
	int		sig;

	sig = job_signaled(job);
	if (sig || (job_suspended(job) && !job_finished(job)))
	{
		if (sig != SIGINT && sig != SIGQUIT && sig != SIGPIPE)
		{
			write(1, "\n", 1);
			job_print_status(job);
		}
	}
	return (1);
}
