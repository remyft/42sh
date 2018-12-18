/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:11:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/18 04:36:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static void		free_args(t_argument **arg)
{
	if (!*arg)
		return ;
	free_args(&(*arg)->next);
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

	cmd = (t_command *)*node;
	if (*node == NULL)
		return ;
	if (cmd->args)
		free_args(&cmd->args);
	if (cmd->redir)
		free_redir(&cmd->redir);
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

t_m_list		*parse_error(const char *buff, t_token *token, t_m_list *lhead)
{
	size_t		i;

	i = token->head;
	ft_putstr_fd("21sh: parse error near `", 2);
	if (token->spec == NEWLINE)
		ft_putstr_fd("\\n", 2);
	else
		write(2, buff + token->head, token->tail - token->head);
	ft_putendl_fd("'", 2);
	free_m_list(&lhead);
	return (NULLLIST);
}
