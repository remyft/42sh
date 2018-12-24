/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 18:06:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/24 02:31:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void		free_args(t_argument **arg)
{
	if (!*arg)
		return ;
	free_args(&(*arg)->next);
	if ((*arg)->result)
		free((*arg)->result);
	free(*arg);
	*arg = NULLARG;
}

static void		free_redir(t_redirection **redir)
{
	if (!*redir)
		return ;
	free_redir(&(*redir)->next);
	free(*redir);
	*redir = NULLREDIR;
}

static void		free_command(void **node)
{
	t_command	*cmd;
	t_pipeline	*pipe;

	cmd = (t_command *)*node;
	pipe = (t_pipeline *)*node;
	if (*node == NULL)
		return ;
	if (cmd->type == IS_A_COMMAND)
	{
		free_args(&cmd->args);
		free_redir(&cmd->redir);
	}
	if (pipe->type == IS_A_PIPE)
	{
		free_command(&pipe->left);
		free_command(&pipe->right);
	}
	free(*node);
	*node = NULL;
}

static void		free_ao_list(t_ao_list **list)
{
	if ((*list) == NULLAOLIST)
		return ;
	free_ao_list(&(*list)->next);
	free_command(&(*list)->cmd);
	free(*list);
	*list = NULL;
}

void			free_m_list(t_m_list **list)
{
	if (*list == NULLLIST)
		return ;
	free_m_list(&(*list)->next);
	if ((*list)->aolist)
		free_ao_list(&(*list)->aolist);
	free(*list);
	*list = NULLLIST;
}
