/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:13:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/18 18:42:06 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "command.h"
#include "command_error.h"
#include "shell_lib.h"
#include "shell_env.h"
#include "job_control.h"

static void		command_execve(char *name, t_jobs *job, t_process *p, t_s_env *e)
{
	pid_t	pid;

	pid = getpid();
	if (!job->pgid)
		job->pgid = pid;
	setpgid(pid, job->pgid);
	if (!e->async)
		tcsetpgrp(0, job->pgid);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGSTOP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	execve(name, ((t_execute *)p->exec)->cmd, ((t_execute *)p->exec)->env);
	exit(EXIT_FAILURE);
}


static void		command_cleanup(char *name, t_execute *exec)
{
	(void)name;
	(void)exec;
	ft_strdel(&name);
	//command_free(exec, NULL);
}

int				command_system(t_jobs *job, t_process *p, t_s_env *e)
{
	char		*name;
	pid_t		pid;
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
		pid = 0;
		//if (e->forked || (pid = fork()) == 0)
		if ((pid = fork()) == 0)
			command_execve(name, job, p, e);
		if (pid > 0)
			command_process(pid, job, p, e);
		else if (pid < 0)
			error = command_error(e->progname, ERR_FORK, exec->cmd, e);
	}
	command_cleanup(name, exec);
	//if (e->forked == 0)
	//	remove_job(&e->jobs, e->job_id);
	return (error);
}
