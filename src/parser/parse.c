/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:00:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/10 06:18:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operator.h"
#include "parser.h"

static t_node	*new_node(t_node *left, t_token *token, t_node *right)
{
	t_node		*new;

	new = ft_memalloc(sizeof(*new));
	if (!new)
		return (new);
	new->left = left;
	new->token = token;
	new->right = right;
	return (new);
}

static t_node	*parse_word(t_command *tail, t_token *token)
{
	if (tail->node == NULLNODE)
	{
		tail->node = new_node(NULLNODE, token, NULLNODE);
		return (tail->node);
	}
	tail->node->left = new_node(NULLNODE, token, NULLNODE);
	return (tail->node->left);
}

static t_node	*parse_operator(t_command *tail, t_token *token)
{
	if (tail->node == NULLNODE)
	{
		tail->node = new_node(NULLNODE, token, NULLNODE);
		return (tail->node);
	}
	if (tail->node->token->type == OPERATOR)
	{
		tail->node->right = new_node(NULLNODE, token, NULLNODE);
		return (tail->node->right);
	}
	return (tail->node);
}

static t_command	*new_tree(t_command **tail)
{
	t_command		*new;

	new = ft_memalloc(sizeof(*new));
	if (!new)
		return (new);
	if (*tail)
		(*tail)->next = new;
	else
		*tail = new;
	return (new);
}

t_command			*parse(const char *buff, t_token *token)
{
	t_command		*head;
	t_command		*tail;
	t_node		*node;

	head = NULLTREE;
	tail = head;
	node = tail->node;
	while (tail && token)
	{
		if (token->type == NEWLINE
			|| (token->type == OPERATOR
				&& (token->spec == 0
					|| token->spec == 4
					|| token->spec == 6)))
			tail = new_tree(&tail);
		else if (token->type == OPERATOR)
			node = parse_operator(tail, token);
		else
			node = parse_word(tail, token);
		token = token->next;
	}
	(void)buff;
	return (head);
}
