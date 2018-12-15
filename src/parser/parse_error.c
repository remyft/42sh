/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:11:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/15 20:06:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void		free_node(t_node **node)
{
	if (*node == NULLNODE)
		return ;
	free_node(&(*node)->left);
	free_node(&(*node)->right);
	free(*node);
	*node = NULLNODE;
}

static void		free_ao_list(t_ao_list **list)
{
	if ((*list) == NULLAOLIST)
		return ;
	free_ao_list(&(*list)->next);
	if ((*list)->node)
		free_node(&(*list)->node);
	free(*list);
	*list = NULLAOLIST;
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
	dprintf(2, "21sh: parse error near `%.*s'\n",
		(int)(token->tail - token->head), buff + token->head);
	free_m_list(&lhead);
	return (NULLLIST);
}
