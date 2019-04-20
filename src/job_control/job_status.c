/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:39:27 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/20 10:30:58 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <sys/ioctl.h>

/*static void	job_foreground(t_jobs *job, t_s_env *e)
{
	ioctl(e->fd, TIOCSPGRP, &job->pgid);
	//tcsetpgrp(0, job->pgid);
	//signal(SIGTTOU, SIG_IGN);
	job_wait(job, e);
	ioctl(e->fd, TIOCSPGRP, &e->pid);
	//tcsetpgrp(0, e->pid);
	//signal(SIGTTOU, SIG_DFL);
	remove_job(&e->jobs, job->id);
}*/
