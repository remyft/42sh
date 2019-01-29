/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:13:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 14:04:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "command.h"
#include "shell_env.h"
#include "shell.h"

static int		fork_error(const char *err, t_s_env *e)
{
	ft_putstr_fd(e->progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	return (1);
}

int				command_fork(t_execute *exec, t_s_env *e)
{
	pid_t		pid;

	term_restore(e->save);
	pid = fork();
	if (pid < 0)
		e->ret = fork_error("fork failed", e);
	else if (pid == 0)
	{
		if (!command_redirect(exec->redirection, e))
			command_execute(exec, e);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &e->ret, 0);
	command_free(exec, e->public_env, NULL);
	define_new_term(&e->save);
	return (0);
}
