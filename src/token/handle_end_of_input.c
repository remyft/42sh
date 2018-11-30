/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end_of_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 23:42:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/01 00:03:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token			*handle_end_of_input(t_param *param, t_call *token)
{
	param->token->tail = param->i;
	if (param->token->type != UNDEFINED
		&& param->token->type != TOKEN
		&& param->token->spec != NEWLINE)
		param->token = token[param->token->type].identifier(param);
	param->token->type = TOKEN;
	param->token->spec = NEWLINE;
	return (param->token->next);
}