/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/07 22:38:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"

static int		command_pipe(t_execute *exec, t_s_env *e)
{
	exec->piped = 1;
	return (command_prepare(exec, e));
}

int				command_parse(void *cmd, t_s_env *e)
{
	t_execute	exec;

	debug_execution(cmd);
	ft_memset(&exec, 0, sizeof(exec));
	if (!((t_command *)cmd)->args)
		return (0);
	exec.variable = ((t_command *)cmd)->args;
	exec.redirection = ((t_command *)cmd)->redir;
	e->ret = (*(int *)cmd == IS_A_PIPE) ?
		command_pipe(&exec, e) : command_prepare(&exec, e);
	return (e->ret);
}
