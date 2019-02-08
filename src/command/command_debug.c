/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 05:00:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/08 02:37:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

#ifndef DEBUG

void			command_debug(t_command *cmd)
{
	(void)cmd;
}

#else

static void		print_args(t_argument **arg, int id)
{
	size_t			i;

	while (*arg && (id || (*arg)->token->id == ASSIGNMENT_WORD))
	{
		i = 0;
		if ((*arg)->cmd)
			while ((*arg)->cmd[i])
				printf("\t[%s]\n", (*arg)->cmd[i++]);
		(*arg) = (*arg)->next;
	}
}

void			command_debug(t_command *cmd)
{
	t_redirection	*red;
	t_argument		*arg;

	if (cmd->type == IS_A_PIPE)
	{
		command_debug(((t_pipeline *)cmd)->left);
		command_debug(((t_pipeline *)cmd)->right);
		return ;
	}
	printf("\nEXECUTION-----------------------\n");
	arg = cmd->args;
	printf("Variables:\n");
	print_args(&arg, 0);
	printf("Arguments :\n");
	print_args(&arg, 1);
	red = cmd->redir;
	printf("\nRedirections :\n");
	while (red)
	{
		arg = red->arg;
		print_args(&arg, 1);
		red = red->next;
	}
	printf("-----------------------------END\n");
}

#endif
