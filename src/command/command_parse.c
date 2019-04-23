/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/22 19:35:17 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"
#include "job_control.h"
#include "command_error.h"
#include "operator_types.h"

int				command_piped(void *cmd, t_s_env *e, int type)
{
	command_parse(((t_pipeline *)cmd)->left, e, type | PIPED);
	if (*(int *)((t_pipeline *)cmd)->right == IS_A_PIPE)
	{
		if (command_piped(((t_pipeline *)cmd)->right, e, PIPED))
			return (1);
	}
	else
		command_parse(((t_pipeline *)cmd)->right, e, END_OF_PIPE);
	return (0);
}

int				command_parse(void *cmd, t_s_env *e, int type)
{
	t_execute	*exec;

	if (*(int *)cmd == IS_A_PIPE)
		return (command_piped(cmd, e, type));
	//command_debug(cmd);
	if (!((t_command *)cmd)->args)
		return (0);
	if (!(exec = ft_memalloc(sizeof(t_execute))))
		return (0);
	exec->async = ((t_command *)cmd)->async;
	exec->variable = ((t_command *)cmd)->args;
	exec->redirection = ((t_command *)cmd)->redir;
	return (command_prepare(exec, e, type));
}
