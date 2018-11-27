/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:05:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/27 19:11:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token			*new_token(const char c, size_t pos)
{
	t_token		*new;

	new = malloc(sizeof(*new));
	if (new == (t_token *)0)
		return ((t_token *)0);
	new->quoted = 0;
	new->type = define_token(c);
	new->spec = UNDEFINED;
	new->head = pos;
	new->tail = pos;
	new->exp = (char *)0;
	new->next = (t_token *)0;
	return (new);
}
