/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/10 19:05:31 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"
#include "job_control.h"
#include "command_error.h"

int				command_parse(void *cmd, t_s_env *e)
{
	t_execute	*exec;

	if (!(exec = ft_memalloc(sizeof(t_execute))))
		return (0);
	if (*(int *)cmd == IS_A_PIPE)
		return (command_pipe(cmd, e, (int[2]){ 0, 0 }));
	//command_debug(cmd);
	//ft_memset(&exec, 0, sizeof(exec));
	if (!((t_command *)cmd)->args)
		return (0);
	exec->async = ((t_command *)cmd)->async;
	exec->variable = ((t_command *)cmd)->args;
	exec->redirection = ((t_command *)cmd)->redir;
	return (command_prepare(exec, e));
}
