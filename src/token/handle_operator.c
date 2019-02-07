/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 20:34:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/07 00:20:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

t_token			*handle_operator(t_param *param, t_call *token)
{
	size_t		len;

	len = (param->buff + param->i) - param->token->head + 1;
	if (param->token->type == UNDEFINED)
		param->token->type = OPERATOR;
	else if (param->token->type != OPERATOR
	|| check_operator(param->token, len) == 0)
		param->token = token[param->token->type].identifier(param);
	return (param->token);
}
