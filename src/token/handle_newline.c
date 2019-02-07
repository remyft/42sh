/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_newline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 07:55:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/06 02:32:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token			*handle_newline(t_param *param, t_call *token)
{
	if (param->token->type != UNDEFINED)
		param->token = token[param->token->type].identifier(param);
	param->token->type = TOKEN;
	param->token->id = NEWLINE;
	(void)param;
	(void)token;
	return (param->token);
}
