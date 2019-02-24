/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:13:28 by gbourgeo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/02/23 16:22:56 by dbaffier         ###   ########.fr       */
=======
/*   Updated: 2019/02/23 17:43:06 by gbourgeo         ###   ########.fr       */
>>>>>>> ae67f43beccf4176e735b3f1aabc8424f9d8a5a7
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "command.h"
#include "command_error.h"
#include "shell_lib.h"
#include "shell_env.h"

static void		command_execve(char *name, t_execute *exec)
{
	execve(name, exec->cmd, exec->env);
	exit(EXIT_FAILURE);
}

static int		command_wait(pid_t pid, t_s_env *e)
{
	waitpid(pid, &e->ret, 0);
	return (e->ret);
}

static void		command_cleanup(char *name, t_execute *exec)
{
	ft_strdel(&name);
	command_restore_fds(exec->fds);
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
			command_execve(name, exec);
		if (pid > 0)
			error = command_wait(pid, e);
		else if (pid < 0)
			error = command_error(e->progname, ERR_FORK_VAL, exec->cmd);
	}
	command_cleanup(name, exec);
	return ((e->ret = error));
}
