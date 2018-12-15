/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:00:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/15 18:35:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operator.h"
#include "parser.h"

static t_node	*new_node(t_token *token)
{
	t_node		*new;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (new);
	new->token = token;
	return (new);
}

static t_node	*parse_word(t_token *token, t_node *ntail, t_ao_list **aolist)
{
	if ((*aolist)->node == NULLNODE)
		return (((*aolist)->node = new_node(token)));
	return ((ntail->left = new_node(token)));
}

static t_node	*parse_operator(t_token *token, t_node **nhead, t_ao_list **aolist)
{
	(void)token;
	(void)nhead;
	(void)aolist;
	return (NULLNODE);
}

static t_m_list		*new_m_list(t_m_list **list)
{
	if ((*list = ft_memalloc(sizeof(**list))) == NULLLIST)
		return (NULLLIST);
	(*list)->mode = UNDEFINED;
	(*list)->aolist = ft_memalloc(sizeof(*(*list)->aolist));
	return (*list);
}

static t_ao_list	*new_ao_list(t_ao_list *aolist)
{
	return ((aolist->next = ft_memalloc(sizeof(*aolist))));
}

t_m_list		*parse(const char *buff, t_token *token)
{
	t_m_list	*lhead;
	t_m_list	*ltail;
	t_ao_list	*aolist;
	t_node		*nhead;
	t_node		*ntail;

	if ((ltail = new_m_list(&lhead)) != NULLLIST)
		aolist = ltail->aolist;
	while (ltail && aolist && token)
	{
		if (token->type == OPERATOR && IS_LIST(token->spec))
		{
			if (token->spec == BACKGRND && aolist->node == NULLNODE)
				return (parse_error(buff, token, lhead));
			ltail->mode = token->spec;
			if ((ltail = new_m_list(&ltail->next)) != NULLLIST)
				aolist = ltail->aolist;
		}
		else if (token->type == OPERATOR && IS_AOLIST(token->spec))
		{
			aolist->mode = token->spec;
			aolist = new_ao_list(aolist);
		}
		else if (token->type == OPERATOR)
			ntail = parse_operator(token, &nhead, &aolist);
		else
			ntail = parse_word(token, ntail, &aolist);
		token = token->next;
	}
#ifdef DEBUG
	debug_parser(buff, lhead);
#endif
	return (lhead);
}
