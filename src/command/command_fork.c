/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:13:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/31 23:25:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "command.h"
#include "command_error.h"
#include "shell_lib.h"
#include "shell_env.h"
#include "shell.h"

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

int				command_fork(t_execute *exec, t_s_env *e)
{
	char		*name;
	pid_t		pid;
	int			error;

	name = NULL;
	if ((error = command_path(&name, exec->cmd[0],
								sh_getnenv("PATH", exec->env))) != ERR_OK_VAL)
		error = command_error(e->progname, error, exec->cmd);
	else if ((error = command_access(name, 0)) != ERR_OK_VAL)
		error = command_error(e->progname, error, exec->cmd);
	else if ((pid = fork()) == 0)
	{
		term_restore(e->save);
		restore_signals_to_default();
		if (!command_redirect(exec->redirection, e))
			execve(name, exec->cmd, exec->env);
		command_error(e->progname, ERR_EXEC_VAL, exec->cmd);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &e->ret, 0);
		define_new_term(&e->save);
	}
	else if (pid < 0)
		error = command_error(e->progname, ERR_FORK_VAL, exec->cmd);
	free(name);
	command_free(exec, e->public_env, NULL);
	return (error);
}
