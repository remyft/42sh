/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end_of_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 23:42:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/23 08:21:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token			*handle_end_of_input(t_param *param, t_call *token)
{
	t_token		*ret;

	param->token->len = (param->buff + param->i) - param->token->head;
	if (param->token->type != UNDEFINED && param->token->id != NEWLINE
		&& param->token->id != COMMENT && param->token->len > 1)
		param->token = token[param->token->type].identifier(param);
	if ((ret = param->token->prev))
	{
		free(ret->next);
		ret->next = NULL;
	}
	return (NULLTOKEN);
}
