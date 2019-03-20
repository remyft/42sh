/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 23:11:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 15:47:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "command_error.h"
#include "shell_lib.h"

int				command_builtin(t_builtin builtin, t_execute *exec, t_s_env *e)
{
	int			error;

	if ((error = command_redirect(exec->fds, exec->redirection)) != ERR_OK)
		command_error(e->progname, error, NULL, e);
	else
		e->ret = builtin(exec, e);
	command_free(exec, NULL);
	if ((error = command_restore_fds(exec->fds)) != ERR_OK)
		command_error(e->progname, error, NULL, e);
	return (ERR_OK);
}
