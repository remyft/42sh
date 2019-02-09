/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/09 07:07:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"

int				command_parse(void *cmd, t_s_env *e)
{
	t_execute	exec;

	command_debug(cmd);
	if (*(int *)cmd == IS_A_PIPE)
		return (command_pipe(cmd, e));
	ft_memset(&exec, 0, sizeof(exec));
	if (!((t_command *)cmd)->args)
		return (0);
	exec.variable = ((t_command *)cmd)->args;
	exec.redirection = ((t_command *)cmd)->redir;
	return (command_prepare(&exec, e));
}
