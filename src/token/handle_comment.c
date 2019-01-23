/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_comment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 00:22:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/23 08:22:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token			*handle_comment(t_param *param, t_call *tokens)
{
	(void)tokens;
	if (param->token->type == UNDEFINED)
	{
		param->token->type = TOKEN;
		param->token->id = COMMENT;
	}
	return (param->token);
}
