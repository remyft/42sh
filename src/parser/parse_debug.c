/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 14:52:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/18 16:39:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "parser.h"
#include "operator_types.h"

#ifndef DEBUG

void			debug_parser(t_m_list *list)
{
	(void)list;
}

#else

static void		print_r(t_command *cmd)
{
	t_redirection	*red;
	t_token			*token;
	size_t			i;

	red = cmd->redir;
	while (red)
	{
		if ((token = red->ionumber))
			dprintf(2, "\t\t\tIONUMBER %.*s\n", (int)token->len, token->head);//
		if ((token = red->token))
			dprintf(2, "\t\t\tREDIR %.*s\n", (int)token->len, token->head); //
		if (red->arg && (token = red->arg->token))
		{
			dprintf(2, "\t\t\t  ARG %.*s\n", (int)token->len, token->head); //
			i = 0;
			while (red->arg->cmd && red->arg->cmd[i])
				ft_dprintf(2, "\t\t\t      %s\n", red->arg->cmd[i++]);
		}
		ft_dprintf(2, "\t\t\t---------------------\n");
		red = red->next;
	}
}

static void		print_command(t_command *cmd)
{
	t_argument	*arg;
	t_token		*token;
	size_t		i;

	if (!cmd)
		return ;
	ft_dprintf(2, "\t\t%s COMMAND\n");
	arg = cmd->args;
	while (arg)
	{
		if ((token = arg->token))
			dprintf(2, "\t\t\tARG %.*s\n", (int)token->len, token->head); //
		i = 0;
		while (arg->cmd && arg->cmd[i])
			ft_dprintf(2, "\t\t\t    %s\n", arg->cmd[i++]);
		arg = arg->next;
	}
	print_r(cmd);
}

static void		print_pipe(t_pipeline *pipe)
{
	if (!pipe)
		return ;
	ft_dprintf(2, "\tPIPED COMMAND\n");
	ft_dprintf(2, "\t\tPIPE LEFT\n");
	pipe->left && *(int *)pipe->left == IS_A_COMMAND ?
		print_command(pipe->left) : print_pipe(pipe->left);
	ft_dprintf(2, "\t\tPIPE RIGHT\n");
	pipe->right && *(int *)pipe->right == IS_A_COMMAND ?
		print_command(pipe->right) : print_pipe(pipe->right);
}

void			debug_parser(t_m_list *list)
{
	t_m_list	*ptr;
	t_ao_list	*ao;

	ptr = list;
	ft_dprintf(2, "\nPARSER--------------------------\n");
	while (ptr)
	{
		ft_dprintf(2, "Main List %s\n", ptr->async ? "asynchronous" : "");
		ao = ptr->aolist;
		while (ao)
		{
			if (ao->type == OR_IF_VALUE)
				ft_dprintf(2, "\tOR COMMAND\n");
			else if (ao->type == AND_IF_VALUE)
				ft_dprintf(2, "\tAND COMMAND\n");
			ao->cmd && *(int *)ao->cmd == IS_A_COMMAND ?
				print_command(ao->cmd) : print_pipe(ao->cmd);
			ao = ao->next;
		}
		ptr = ptr->next;
	}
	ft_dprintf(2, "------------------------------END\n");
}

#endif
