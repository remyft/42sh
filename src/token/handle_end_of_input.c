/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end_of_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 23:42:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/02 23:09:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token			*handle_end_of_input(t_param *param, t_call *token)
{
	param->token->tail = param->i;
	if (param->token->type != UNDEFINED
		&& param->token->type != TOKEN
		&& param->token->spec != NEWLINE)
	{
		param->token = token[param->token->type].identifier(param);
		param->token->type = TOKEN;
		param->token->spec = NEWLINE;
	}
	if (param->token->type == UNDEFINED)
	{
		param->token->type = TOKEN;
		param->token->spec = NEWLINE;
	}
	return (param->token->next);
}
