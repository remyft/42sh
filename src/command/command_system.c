/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:13:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 15:47:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "command.h"
#include "command_error.h"
#include "shell_lib.h"
#include "shell_env.h"
#include "shell_term.h"

static void		command_execve(char *name, t_execute *exec, t_s_env *e)
{
	pid_t		pid;

	pid = 0;
	term_restore(e->save);
	if (e->forked || (pid = fork()) == 0)
	{
		execve(name, exec->cmd, exec->env);
		exit(EXIT_FAILURE);
	}
	if (pid > 0)
		command_wait(pid, 0, &e->ret);
	else if (pid < 0)
		e->ret = command_error(e->progname, ERR_FORK, exec->cmd, e);
	define_new_term(&e->save);
}

static void		command_cleanup(char *name, t_execute *exec)
{
	ft_strdel(&name);
	command_free(exec, NULL);
}

int				command_system(t_execute *exec, t_s_env *e)
{
	char		*name;
	int			error;

	name = NULL;
	if ((error = command_path(&name, exec->cmd[0],
	sh_getnenv("PATH", exec->env))))
		command_error(e->progname, error, exec->cmd, e);
	else if ((error = command_access(name, exec->cmd[0])))
		command_error(e->progname, error, exec->cmd, e);
	else if ((error = command_redirect(exec->fds, exec->redirection)))
		command_error(e->progname, error, NULL, e);
	else
		command_execve(name, exec, e);
	command_cleanup(name, exec);
	if (command_restore_fds(exec->fds))
		command_error(e->progname, ERR_DUP2, NULL, e);
	return (ERR_OK);
}
