/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:38:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/09 16:21:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

t_quote			*quote_add(t_quote **head, int type)
{
	if (*head)
		(*head)->next = quote_add(&(*head)->next, type);
	else if ((*head = ft_memalloc(sizeof(**head))))
	{
		(*head)->type = type;
		return (*head);
	}
	if (*head && !(*head)->next)
	{
		free(*head);
		*head = NULLQUOTE;
	}
	return (*head);
}

void			quote_remove(t_quote **head, int type)
{
	if (!*head)
		return ;
	if ((*head)->next)
		return (quote_remove(&(*head)->next, type));
	if ((*head)->type == type)
	{
		free(*head);
		*head = NULLQUOTE;
	}
}

int				quote_type(t_quote *head)
{
	if (!head)
		return (NO_QUOTE);
	if (head->next)
		return (quote_type(head->next));
	return (head->type);
}
