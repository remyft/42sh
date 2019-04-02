/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_newline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:16:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/02 18:11:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "operator_types.h"

t_token			*handle_newline(t_param *param, t_call *token)
{
	if (!param->token->prev)
		return (param->token);
	if (param->token->type != UNDEFINED)
		param->token = token[param->token->type].identifier(param);
	if (param->token->prev->type != OPERATOR
	|| param->token->prev->id != NEWLINE_VALUE)
		param->token->type = OPERATOR;
	return (param->token);
}
