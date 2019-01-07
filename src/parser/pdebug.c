/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdebug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 14:52:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/07 20:18:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#ifndef DEBUG

void			debug_parser(const char *buff, t_m_list *list)
{
	(void)buff;
	(void)list;
}

#else

# define PC(b, p) print_command(b, p)
# define PP(b, p) print_pipe(b, p)
# define TYPE(b, p) (p && *(int *)p == IS_A_COMMAND) ? PC(b, p) : PP(b, p)

static void		print_r(const char *buff, t_command *cmd)
{
	t_redirection	*red;
	t_token			*token;
	size_t		i;

	red = cmd->redir;
	while (red)
	{
		token = red->token;
		if (token)
			printf("\t\t\tREDIR %.*s\n", (int)(token->tail - token->head),
										buff + token->head);
		if ((token = red->ionumber))
			printf("\t\t\tIONUMBER %.*s\n", (int)(token->tail - token->head),
										buff + token->head);
		if (red->arg && (token = red->arg->token))
			printf("\t\t\tREDIR ARG %.*s\n", (int)(token->tail - token->head),
										buff + token->head);
		i = 0;
		while (red->arg && red->arg->list && red->arg->list[i])
			printf("\t\t\t    %s\n", red->arg->list[i++]);
		red = red->next;
	}
}

static void		print_command(const char *buff, t_command *cmd)
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
		printf("\t\t\tARG %.*s\n", (int)(token->tail - token->head),
									buff + token->head);
		i = 0;
		while (arg->list && arg->list[i])
			printf("\t\t\t    %s\n", arg->list[i++]);
		arg = arg->next;
	}
	print_r(buff, cmd);
}

static void		print_pipe(const char *buff, t_pipeline *pipe)
{
	if (!pipe)
		return ;
	printf("\t\tPIPE LEFT\n");
	TYPE(buff, pipe->left);
	printf("\t\tPIPE RIGHT\n");
	TYPE(buff, pipe->right);
}

void			debug_parser(const char *buff, t_m_list *list)
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
			TYPE(buff, ao->cmd);
			ao = ao->next;
		}
		ptr = ptr->next;
	}
	printf("-------------------------------END\n");
}

#endif
