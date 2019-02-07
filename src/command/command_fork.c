/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:13:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/07 03:04:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "command.h"
#include "command_error.h"
#include "shell_lib.h"
#include "shell_env.h"
#include "shell.h"
#include "ft_printf.h"
static void		command_execve(char *name, t_execute *exec)
{
	ft_printf("executing %s\n", name);
	execve(name, exec->cmd, exec->env);
	exit(EXIT_FAILURE);
}

static int		command_wait(pid_t pid, t_s_env *e)
{
	waitpid(pid, &e->ret, 0);
	return (e->ret);
}

static void		command_ret(char *name, t_execute *exec, t_s_env *e)
{
	ft_strdel(&name);
	command_restore_fds(exec->fds);
	define_new_term(&e->save);
	command_free(exec, e->public_env, NULL);
}

int				command_fork(t_execute *exec, t_s_env *e)
{
	char		*name;
	pid_t		pid;
	int			error;

	name = NULL;
	term_restore(e->save);
	if ((error = command_path(&name, exec->cmd[0],
				sh_getnenv("PATH", exec->env))) != ERR_OK_VAL)
		error = command_error(e->progname, error, exec->cmd);
	else if ((error = command_access(name, exec->cmd[0][0] == '/')) != ERR_OK_VAL)
		error = command_error(e->progname, error, exec->cmd);
	else if (!command_redirect(exec->fds, exec->redirection, e))
	{
		ft_printf("IS FORKED %d\n", e->forked);
		if (e->forked || (pid = fork()) == 0)
			command_execve(name, exec);
		else if (pid > 0)
			error = command_wait(pid, e);
		else if (pid < 0)
			error = command_error(e->progname, ERR_FORK_VAL, exec->cmd);
	}
	command_ret(name, exec, e);
	return ((e->ret = error));
}
