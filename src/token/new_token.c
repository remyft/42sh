/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:05:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/29 19:58:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static int		define_token(int c)
{
	if (ft_isspace(c))
		return (UNDEFINED);
	if (ft_isoperator(c))
		return (OPERATOR);
	return (TOKEN);
}

t_token			*new_token(int c, size_t pos)
{
	t_token		*new;

	new = malloc(sizeof(*new));
	if (new == (t_token *)0)
		return ((t_token *)0);
	new->quote = 0;
	new->type = define_token(c);
	new->spec = 0;
	new->head = pos;
	new->tail = pos;
	new->exp = (char *)0;
	new->next = (t_token *)0;
	return (new);
}
