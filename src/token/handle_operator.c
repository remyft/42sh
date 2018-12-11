/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 20:34:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/11 07:17:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

t_token			*handle_operator(t_param *param, t_call *token)
{
	if (param->token->type == UNDEFINED)
		param->token->type = OPERATOR;
	else if (param->token->type != OPERATOR)
		return (token[param->token->type].identifier(param));
	return (param->token);
}
