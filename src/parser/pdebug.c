/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdebug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 14:52:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/18 02:26:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define TYPE(buff, ptr)	(ptr && *(int *)ptr == IS_COMMAND) ? print_command(buff, ptr) : print_pipe(buff, ptr)

static void		print_command(const char *buff, t_command *cmd)
{
	if (!cmd)
		return ;
	printf("\t\tCOMMAND (type : %d)\n", cmd->type);
	t_argument *arg = cmd->args;
	while (arg)
	{
		t_token *token = arg->token;
		printf("\t\t\tARG %.*s\n", (int)(token->tail - token->head), buff + token->head);
		arg = arg->next;
	}
	t_redirection *red = cmd->redir;
	while (red)
	{
		t_token *token = red->token;
		if (token)
			printf("\t\t\tREDIR %.*s\n", (int)(token->tail - token->head), buff + token->head);
		if ((token = red->ionumber))
			printf("\t\t\tIONUMBER %.*s\n", (int)(token->tail - token->head), buff + token->head);
		if ((token = red->arg))
			printf("\t\t\tREDIR ARG %.*s\n", (int)(token->tail - token->head), buff + token->head);
		red = red->next;
	}
}

static void	print_pipe(const char *buff, t_pipeline *pipe)
{
	if (!pipe)
		return ;
	printf("\t\tPIPE LEFT\n");
	TYPE(buff, pipe->left);
	printf("\t\tPIPE RIGHT\n");
	TYPE(buff, pipe->right);
}

void		debug_parser(const char *buff, t_m_list *list)
{
	for (t_m_list *ptr = list; ptr; ptr = ptr->next)
	{
		printf(" Main List (mode : %d)\n", ptr->mode);
		for (t_ao_list *ao = ptr->aolist; ao; ao = ao->next)
		{
			printf("\tAND OR LIST (mode : %d)\n", ao->mode);
			TYPE(buff, ao->cmd);
		}
	}
}