/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 15:16:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"

int				command_parse(void *cmd, t_s_env *e)
{
	t_execute	exec;

	if (*(int *)cmd == IS_A_PIPE)
		return (command_pipe(cmd, e, (int[2]){ 0, 0 }));
	command_debug(cmd);
	if (!((t_command *)cmd)->args)
		return (0);
	ft_memset(&exec, 0, sizeof(exec));
	exec.variable = ((t_command *)cmd)->args;
	exec.redirection = ((t_command *)cmd)->redir;
	return (command_prepare(&exec, e));
}
