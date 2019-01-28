/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/28 20:45:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execution.h"

static int		command_pipe(t_execute *exec, t_s_env *e)
{
	exec->piped = 1;
	return (command_fork(exec, e));
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
	if (*(int *)cmd == IS_A_PIPE)
		return (command_pipe(&exec, e));
	return (command_normal(&exec, e));
}
