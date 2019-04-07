/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:13:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/07 17:06:17 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "command.h"
#include "command_error.h"
#include "shell_lib.h"
#include "shell_env.h"
#include "job_control.h"
#include <sys/ioctl.h>
#include "ft_dprintf.h"
#include "signal_intern.h"

static int	dup2_and_close(t_process *p, int from, int to)
{
	if (to != from)
	{
		if (to == -1 && from > 0)
			close(from);
		else
		{
			dup2(to, from);
			if (!(to == STDERR_FILENO && from == STDOUT_FILENO)
					&& !(to == STDOUT_FILENO && from == STDERR_FILENO))
				if (to > 3 && to != -1)
					close(to);
		}
	}
	if (from == STDIN_FILENO)
	{
		if (p->pipe[0] != -1)
			close(p->pipe[0]);
		if (p->pipe[1] != -1)
			close(p->pipe[1]);
	}
	return (1);
}

static void		command_setup(t_process *p)
{
	if (p->fds[2] == STDERR_FILENO)
	{
		dup2_and_close(p, STDERR_FILENO, p->fds[2]);
		dup2_and_close(p, STDOUT_FILENO, p->fds[1]);
	
	}
	else
	{
		dup2_and_close(p, STDOUT_FILENO, p->fds[1]);
		dup2_and_close(p, STDERR_FILENO, p->fds[2]);
	}
	dup2_and_close(p, STDIN_FILENO, p->fds[0]);
}

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
		ft_dprintf(2, "21sh: signal to default with process %d failed\n", p->pid);
		exit(EXIT_FAILURE);
	}
	command_setup(p);
	execve(name, ((t_execute *)p->exec)->cmd, ((t_execute *)p->exec)->env);
	exit(EXIT_FAILURE);
}

int				command_system(t_jobs *job, t_process *p, t_s_env *e)
{
	char		*name;
	int			error;
	t_execute	*exec;

	name = NULL;
	exec = (t_execute *)p->exec;
	if ((error = command_path(&name, exec->cmd[0],
				sh_getnenv("PATH", exec->env))) != ERR_OK)
		error = command_error(e->progname, error, exec->cmd, e);
	else if ((error = command_access(name, exec->cmd[0])) != ERR_OK)
		error = command_error(e->progname, error, exec->cmd, e);
	else if (!command_redirect(exec->fds, exec->redirection, e))
	{
		if (e->forked || (p->pid = fork()) == 0)
			command_execve(name, job, p, e);
		else if (p->pid < 0)
			error = command_error(e->progname, ERR_FORK, exec->cmd, e);
		else if (e->interactive)
			command_process(p->pid, e->pid, job, p);
	}
	ft_strdel(&name);
	//return (1);
	return (error);
}
