/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:13:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/06 11:09:21 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "command.h"
#include "command_error.h"
#include "shell_lib.h"
#include "shell_env.h"
#include "job_control.h"

static void		command_execve(char *name, t_execute *exec, t_s_env *e)
{
	t_jobs		*job;
	t_process	*proc;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGSTOP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	job = get_job_by_id(e->job_id, e->jobs);
	proc = job->process;
	proc->pid = getpid();
	if (job->pgid > 0)
		setpgid(0, job->pgid);
	else
	{
		job->pgid = proc->pid;
		setpgid(0, job->pgid);
	}
	execve(name, exec->cmd, exec->env);
	exit(EXIT_FAILURE);
}


static void		command_cleanup(char *name, t_execute *exec)
{
	ft_strdel(&name);
	command_free(exec, NULL);
}

int				command_system(t_execute *exec, t_s_env *e)
{
	char		*name;
	pid_t		pid;
	int			error;

	name = NULL;
	if ((error = command_path(&name, exec->cmd[0],
				sh_getnenv("PATH", exec->env))) != ERR_OK)
		error = command_error(e->progname, error, exec->cmd, e);
	else if ((error = command_access(name, exec->cmd[0])) != ERR_OK)
		error = command_error(e->progname, error, exec->cmd, e);
	else if (!command_redirect(exec->fds, exec->redirection, e))
	{
		pid = 0;
		if (e->forked || (pid = fork()) == 0)
			command_execve(name, exec, e);
		if (pid > 0)
			command_wait2(pid, exec, e);
		else if (pid < 0)
			error = command_error(e->progname, ERR_FORK, exec->cmd, e);
	}
	remove_job(&e->jobs, e->job_id);
	command_cleanup(name, exec);
	error += command_restore_fds(exec->fds);
	return (error);
}
