/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 18:06:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/24 06:26:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>

static void		free_args(t_argument **arg)
{
	size_t		i;

	if (!*arg)
		return ;
	free_args(&(*arg)->next);
	i = 0;
	if ((*arg)->cmd)
	{
		while ((*arg)->cmd[i])
			free((*arg)->cmd[i++]);
		free((*arg)->cmd);
	}
	free(*arg);
	*arg = NULLARG;
}

static void		free_redir(t_redirection **redir)
{
	if (!*redir)
		return ;
	free_redir(&(*redir)->next);
	if ((*redir)->arg)
		free_args(&(*redir)->arg);
	if ((*redir)->fdarg > 2)
		close((*redir)->fdarg);
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
