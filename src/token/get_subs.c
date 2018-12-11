/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 01:05:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/11 14:45:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/*
** Problem here if param->token->subs in not NULL.
*/

static t_token	*get_token_end(t_token *token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}

t_token			*get_subs(t_param *param, int (*ft_end)(const char *), size_t i)
{
	t_token		*ptr;

	if ((ptr = get_token_end(param->token->subs)) != NULLTOKEN)
		ptr->next = tokenise(param->buff, param->i + i, ft_end, param->depth);
	else
		param->token->subs = tokenise(param->buff, param->i + i, ft_end,
										param->depth);
	if ((ptr = get_token_end(param->token->subs)) != NULLTOKEN)
	{
		param->token->tail = ptr->tail;
		param->i = ptr->tail - !i;
	}
	return (param->token);
}
