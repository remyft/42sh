/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 23:11:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/08 00:14:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "command_error.h"
#include "shell_lib.h"

int				command_builtin(int (*builtin)(t_execute *, t_s_env *),
t_execute *exec, t_s_env *e)
{
	int			ret;

	if (exec->variable == exec->command)
		exec->env = e->public_env;
	else if (!(exec->env = sh_tabdup((const char **)e->public_env))
		|| !(exec->env = modify_environ(exec->variable, exec)))
		return (command_error(e->progname, ERR_MALLOC_VAL, exec->cmd));
	if (!(ret = command_redirect(exec->fds, exec->redirection, e)))
		ret = builtin(exec, e);
	command_restore_fds(exec->fds);
	command_free(exec, e->public_env, NULL);
	return (ret);
}
