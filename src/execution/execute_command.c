/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 01:26:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/22 07:45:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execution.h"
#include "execution_error.h"
#include "expansion_lib.h"

static int		fork_error(const char *err, t_s_env *e)
{
	ft_putstr_fd(e->progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	return (1);
}

static void		execute_free(char **env, char **cmd, char *name)
{
	size_t		i;

	i = 0;
	if (env)
	{
		while (env[i])
			free(env[i++]);
		free(env);
	}
	if (cmd)
		free(cmd);
	if (name)
		free(name);
}

static void		execute_error(char *progname, int err, char **cmd)
{
	static char	*error[] = {
		"", ERR_MALLOC_FUNC, ERR_NOT_FOUND_FUNC, ERR_PERM_FUNC,
	};

	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (cmd && cmd[0])
	{
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(error[err], STDERR_FILENO);
}

static void		execute_command(t_execute *exec, t_s_env *e)
{
	char		**envcpy;
	char		**command;
	char		*name;
	int			error;

	envcpy = NULL;
	command = NULL;
	name = NULL;
	if (!(envcpy = duplicate_environ(e->public_env))
		|| !(envcpy = modify_environ(exec->variable, exec->command, envcpy))
		|| !(command = group_command(exec->command)))
		execute_error(e->progname, ERR_MALLOC_VAL, command);
	else if ((error = path_command(&name, command[0],
									exp_getnenv("PATH", envcpy))) != ERR_OK_VAL)
		execute_error(e->progname, error, command);
	else if ((error = access_command(name)) != ERR_OK_VAL)
		execute_error(e->progname, error, command);
	else
		execve(name, command, envcpy);
	execute_free(envcpy, command, name);
	exit(-1);
}

int				fork_command(t_execute *exec, t_s_env *e)
{
	pid_t		pid;

	// if (!piped)
	// {
	// 	if (is_builtin())
	// 	{
	// 		e->ret = launch_builtin();
	// 		return (0);
	// 	}
	// }

	pid = fork();
	if (pid < 0)
		return (fork_error("fork failed.", e));
	if (pid == 0)
	{
		forked_command(exec, e);
	}
	else
		waitpid(pid, &e->ret, 0);
	return (0);
}
