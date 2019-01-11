/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end_of_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 23:42:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/10 23:47:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token			*handle_end_of_input(t_param *param, t_call *token)
{
	t_token		*ret;

	param->token->tail = param->i;
	if (param->token->type != UNDEFINED && param->token->id != NEWLINE
		&& param->token->head < param->token->tail)
		param->token = token[param->token->type].identifier(param);
	if ((ret = param->token->prev))
	{
		free(ret->next);
		ret->next = NULL;
	}
	return (NULLTOKEN);
}
