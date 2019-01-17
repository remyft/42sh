/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_comment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 00:22:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/10 23:46:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token			*handle_comment(t_param *param, t_call *tokens)
{
	(void)tokens;
	param->token->tail = param->i;
	param->token->type = TOKEN;
	if (!param->token->id)
		param->token->id = COMMENT;
	return (param->token);
}
