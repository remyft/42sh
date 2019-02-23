/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 14:52:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/23 22:21:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "parser.h"

#ifndef DEBUG

void			debug_parser(t_m_list *list)
{
	(void)list;
}

#else

# define PC(p) print_command(p)
# define PP(p) print_pipe(p)
# define TYPE(p) (p && *(int *)p == IS_A_COMMAND) ? PC(p) : PP(p)
# define ERR 2

static void		print_r(t_command *cmd)
{
	t_redirection	*red;
	t_token			*token;
	t_hdoc			*hdoc;
	size_t			i;

	red = cmd->redir;
	while (red)
	{
		if ((token = red->ionumber))
			dprintf(2, "\t\t\tIONUMBER %.*s\n",
				(int)token->len, token->head); //
		if ((token = red->token))
			dprintf(2, "\t\t\tREDIR %.*s\n", (int)token->len, token->head);
		if (red->arg && (token = red->arg->token))
		{
			dprintf(2, "\t\t\t  ARG %.*s\n", (int)token->len, token->head);
			i = 0;
			while (red->arg->cmd && red->arg->cmd[i])
				ft_dprintf(2, "\t\t\t      %s\n", red->arg->cmd[i++]);
		}
		if ((hdoc = red->heredoc))
			dprintf(2, "\t\t\t  HDOC %.*s\n", (int)hdoc->len, hdoc->head);
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
	ft_dprintf(2, "\t\tCOMMAND (type : %d)\n", cmd->type);
	arg = cmd->args;
	while (arg)
	{
		token = arg->token;
		dprintf(2, "\t\t\tARG %.*s\n",
			(int)token->len, token->head);
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
	ft_dprintf(2, "\t\tPIPE LEFT\n");
	TYPE(pipe->left);
	ft_dprintf(2, "\t\tPIPE RIGHT\n");
	TYPE(pipe->right);
}

void			debug_parser(t_m_list *list)
{
	t_m_list	*ptr;
	t_ao_list	*ao;

	ptr = list;
	ft_dprintf(2, "\nPARSER--------------------------\n");
	while (ptr)
	{
		ft_dprintf(2, "Main List (mode : %d)\n", ptr->mode);
		ao = ptr->aolist;
		while (ao)
		{
			ft_dprintf(2, "\tAND OR LIST (mode : %d)\n", ao->mode);
			TYPE(ao->cmd);
			ao = ao->next;
		}
		ptr = ptr->next;
	}
	ft_dprintf(2, "------------------------------END\n");
}

#endif
