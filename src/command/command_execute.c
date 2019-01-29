/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:02:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/28 20:00:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "shell_lib.h"
#include "command.h"
#include "command_error.h"

#ifdef __linux__
# define NSIG _NSIG
#endif

static void		restore_signals_to_default(void)
{
	size_t		i;

	i = 0;
	while (i < NSIG)
		signal(i++, SIG_DFL);
}

void			command_execute(t_execute *exec, t_s_env *e)
{
	char		*name;
	int			error;

	name = NULL;
	if (!(exec->env = sh_tabdup((const char **)e->public_env))
		|| !(exec->env = modify_environ(exec->variable, exec)))
		command_error(e->progname, ERR_MALLOC_VAL, exec->cmd);
	else if ((error = command_path(&name, exec->cmd[0],
								sh_getnenv("PATH", exec->env))) != ERR_OK_VAL)
		command_error(e->progname, error, exec->cmd);
	else if ((error = command_access(name)) != ERR_OK_VAL)
		command_error(e->progname, error, exec->cmd);
	else
	{
		restore_signals_to_default();
		execve(name, exec->cmd, exec->env);
		command_error(e->progname, ERR_EXEC_VAL, exec->cmd);
	}
	free(name);
}
