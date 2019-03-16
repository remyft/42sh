/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 23:11:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/11 17:57:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "command_error.h"
#include "shell_lib.h"

int				command_builtin(t_builtin builtin, t_execute *exec, t_s_env *e)
{
	int			ret;

	if (!(ret = command_redirect(exec->fds, exec->redirection, e)))
		e->ret = builtin(exec, e);
	command_free(exec, NULL);
	ret += command_restore_fds(exec->fds);
	return (ret);
}
