/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdebug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 14:52:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/24 07:42:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void		print_r(t_command *cmd)
{
	t_redirection	*red;
	t_token			*token;
	size_t			i;

	red = cmd->redir;
	while (red)
	{
		if ((token = red->ionumber))
			printf("\t\t\tIONUMBER %.*s\n", (int)token->len, token->head);
		if ((token = red->token))
			printf("\t\t\tREDIR %.*s\n", (int)token->len, token->head);
		if (red->arg && (token = red->arg->token))
			printf("\t\t\tREDIR ARG %.*s\n", (int)token->len, token->head);
		i = 0;
		while (red->arg && red->arg->cmd && red->arg->cmd[i])
			printf("\t\t\t    %s\n", red->arg->cmd[i++]);
		printf("\t\t\t---------------------\n");
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
	printf("\t\tCOMMAND (type : %d)\n", cmd->type);
	arg = cmd->args;
	while (arg)
	{
		token = arg->token;
		printf("\t\t\tARG %.*s\n", (int)token->len, token->head);
		i = 0;
		while (arg->cmd && arg->cmd[i])
			printf("\t\t\t    %s\n", arg->cmd[i++]);
		arg = arg->next;
	}
	print_r(cmd);
}

static void		print_pipe(t_pipeline *pipe)
{
	if (!pipe)
		return ;
	printf("\t\tPIPE LEFT\n");
	TYPE(pipe->left);
	printf("\t\tPIPE RIGHT\n");
	TYPE(pipe->right);
}

void			debug_parser(t_m_list *list)
{
	t_m_list	*ptr;
	t_ao_list	*ao;

	ptr = list;
	printf("\nPARSER--------------------------\n");
	while (ptr)
	{
		printf("Main List (mode : %d)\n", ptr->mode);
		ao = ptr->aolist;
		while (ao)
		{
			printf("\tAND OR LIST (mode : %d)\n", ao->mode);
			TYPE(ao->cmd);
			ao = ao->next;
		}
		ptr = ptr->next;
	}
	printf("------------------------------END\n");
}

#endif
