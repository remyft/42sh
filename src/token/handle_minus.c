/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_minus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 05:48:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/24 07:40:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token				*handle_minus(t_param *param, t_call *token)
{
	(void)token;
	if (param->token->type == UNDEFINED)
	{
		param->token->type = TOKEN;
		return (param->token);
	}
	else if (param->token->type == TOKEN)
		return (param->token);
	param->token = token[param->token->type].identifier(param);
	if (param->token->prev->head[param->token->prev->len - 1] != '&')
		return (param->token);
	param->token->next = new_token(param->buff, param->i + 1);
	param->token->next->prev = param->token;
	param->token->len++;
	return (param->token->next);
}