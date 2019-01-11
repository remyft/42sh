/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 05:00:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/11 05:48:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

#ifndef DEBUG

void			debug_execution(t_command *cmd)
{
	(void)cmd;
}

#else

static void		print_args(t_argument *arg)
{
	size_t			i;

	while (arg)
	{
		i = 0;
		if (arg->list)
			while (arg->list[i])
				printf("\t%s\n", arg->list[i++]);
		arg = arg->next;
	}
}

void			debug_execution(t_command *cmd)
{
	t_redirection	*red;

	printf("\nEXECUTION-----------------------\n");
	printf("Arguments :\n");
	print_args(cmd->args);
	red = cmd->redir;
	printf("\nRedirections :\n");
	while (red)
	{
		print_args(red->arg);
		red = red->next;
	}
	printf("-----------------------------END\n");
}

#endif
