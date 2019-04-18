/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 19:07:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/17 19:19:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "quote.h"

t_hdoc			*hdoc_add(t_hdoc **head, void *token, size_t line)
{
	if (*head)
		(*head)->next = hdoc_add(&(*head)->next, token, line);
	else if ((*head = ft_memalloc(sizeof(**head))))
	{
		(*head)->token = token;
		(*head)->line = line;
		return (*head);
	}
	if (*head && !(*head)->next)
	{
		free(*head);
		*head = NULLHDOC;
	}
	return (*head);
}

void			hdoc_remove(t_hdoc **head)
{
	if (!*head)
		return ;
	if ((*head)->next)
		hdoc_remove(&(*head)->next);
	else
	{
		free(*head);
		*head = NULLHDOC;
	}
}
