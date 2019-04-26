/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:13:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/26 10:33:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell_lib.h"
#include "command.h"
#include "command_error.h"
#include "shell_env.h"
#include "job_control.h"
#include <sys/ioctl.h>
#include "ft_dprintf.h"
#include "signal_intern.h"
#include "redirection.h"


static void		command_execve(char *name, t_jobs *job, t_process *p, t_s_env *e)
{
	p->pid = getpid();
	if (job->pgid == 0)
		job->pgid = p->pid;
	setpgid(p->pid, job->pgid);
	if (job->foreground == 0)
		ioctl(e->fd, TIOCSPGRP, &job->pgid);
	if (signal_to_default() == 1)
	{
		ft_dprintf(2, "%s: signal to default with process %d failed\n",
		e->progname, p->pid);
		exit(EXIT_FAILURE);
	}
	command_setup(p);
	command_builtin_forked(job, p, e);
	execve(name, ((t_execute *)p->exec)->cmd, ((t_execute *)p->exec)->env);
	exit(0);
}

static void		command_exec_job(char *name, t_jobs *job, t_process *p, t_s_env *e)
{
	size_t		len;
	t_execute	*exec;

	exec = (t_execute *)p->exec;
	if (e->forked || (p->pid = fork()) == 0)
	{
		len = sh_tablen((const char **)exec->env);
		len -= sh_tablen((const char **)e->private_env);
		exec->env[len] = NULL;
		if (job->foreground)
			command_rd_forked(((t_execute *)p->exec)->redirection, e);
		command_execve(name, job, p, e);
	}
	else if (p->pid < 0)
		*e->ret = command_error(e->progname, ERR_FORK, exec->cmd, e);
	else if (e->interactive)
		command_process(p->pid, e->pid, job, p);
}

#include <stdio.h>

int				command_system(t_jobs *job, t_process *p, t_s_env *e)
{
	char		*name;
	int			error;
	int			status;
	t_execute	*exec;

	name = NULL;
	status = ERR_OK;
	exec = (t_execute *)p->exec;
	if ((error = command_redirect(exec->fds, exec->redirection)))
		status = command_error(e->progname, error, NULL, e);
	//if ((error = command_redirect_test(p)))
	//	command_error(e->progname, error, NULL, e);
	if (command_is_builtin(p))
		command_exec_job(name, job, p, e);
	else if ((error = command_path(&name, exec->cmd[0],
	sh_getnenv("PATH", exec->env))))
		status = command_error(e->progname, error, exec->cmd, e);
	else if ((error = command_access(name, exec->cmd[0])))
		status = command_error(e->progname, error, exec->cmd, e);
	else
		command_exec_job(name, job, p, e);
	ft_strdel(&name);
	if (status != 0)
		job->status |= JOB_NOTIFIED;
	if ((error = command_restore_fds(exec->fds)))
		status = command_error(e->progname, error, NULL, e);
	return (status);
}
