/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 23:11:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/10 14:54:19 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "command_error.h"
#include "shell_lib.h"
#include "job_control.h"

int				command_builtin(t_builtin builtin, t_jobs *job, t_process *p, t_s_env *e)
{
	int			ret;
	t_execute	*exec;

	job->status |= JOB_BUILTIN_INTERN;
	exec = (t_execute *)p->exec;
	if (!(ret = command_redirect(exec->fds, exec->redirection, e)))
		e->ret = builtin(exec, e);
	job->status |= JOB_NOTIFIED; 
	return (ret);
}
