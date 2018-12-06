/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 01:05:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/06 01:06:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/*
** Problem here if param->token->subs in not NULL.
*/

t_token			*get_subs(t_param *param, int (*ft_end)(const char *), size_t i)
{
	t_token		*ptr;

	param->token->subs = get_tokens(param->buff, param->i + i, ft_end);
	ptr = param->token->subs;
	while (ptr && ptr->next)
		ptr = ptr->next;
	if (ptr)
	{
		param->token->tail = ptr->tail;
		param->i = ptr->tail;
	}
	return (param->token);
}
