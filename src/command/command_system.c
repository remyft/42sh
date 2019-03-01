/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:13:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/01 18:36:49 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "command.h"
#include "command_error.h"
#include "shell_lib.h"
#include "shell_env.h"
#include "job_insert.h"

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
	job = get_job_by_id(exec->job_id, e->jobs);
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
				sh_getnenv("PATH", exec->env))) != ERR_OK_VAL)
		error = command_error(e->progname, error, exec->cmd);
	else if ((error = command_access(name, **exec->cmd == '/')) != ERR_OK_VAL)
		error = command_error(e->progname, error, exec->cmd);
	else if (!command_redirect(exec->fds, exec->redirection, e))
	{
		pid = 0;
		if (e->forked || (pid = fork()) == 0)
			command_execve(name, exec, e);
		if (pid > 0)
		{
			error = command_wait2(pid, exec, e);
	//		error = command_wait(pid, exec->command->async, &e->ret);
		}
		else if (pid < 0)
			error = command_error(e->progname, ERR_FORK_VAL, exec->cmd);
	}
	t_jobs	*jobs;

	dprintf(2, "hi\n");
	jobs = e->jobs;
	while (jobs)
	{
		printf("Hello\n");
		jobs = jobs->next;
	}
	command_cleanup(name, exec);
	return (command_restore_fds(exec->fds));
}
