/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 01:26:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/24 06:01:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execution.h"
#include "execution_error.h"
#include "expansion_lib.h"

void			term_restore(struct termios save);	
void			define_new_term(struct termios *save);
void			set_signal(void);

static void		restore_signals_to_default(void)
{
	size_t		i;

	i = 0;
	while (i < NSIG)
		signal(i++, SIG_DFL);
}

static int		fork_error(const char *err, t_s_env *e)
{
	ft_putstr_fd(e->progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
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

void			execute_command(t_execute *exec, t_s_env *e)
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
	{
		restore_signals_to_default();
		execve(name, command, envcpy);
		execute_error(e->progname, 0, command);
	}
	execute_free(envcpy, command, name);
}

static int		redirect_command(t_redirection *redirection, t_s_env *e)
{
	while (redirection)
	{
		// dprintf(0, "[%d %d]\n", redirection->fdio, redirection->fdarg);
		if (dup2(redirection->fdarg, redirection->fdio) < 0)
			return (fork_error("dup2 failed.", e));
		redirection = redirection->next;
	}
	return (0);
}

int				fork_command(t_execute *exec, t_s_env *e)
{
	pid_t		pid;

	term_restore(*e->save);
	pid = fork();
	if (pid < 0)
		fork_error("fork failed", e);
	else if (pid == 0)
	{
		if (!redirect_command(exec->redirection, e))
			execute_command(exec, e);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &e->ret, 0);
	define_new_term(e->save);
	return (0);
}
