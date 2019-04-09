/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 23:11:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/09 17:19:12 by dbaffier         ###   ########.fr       */
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
	return (ret);
}
