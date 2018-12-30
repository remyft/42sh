/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:35:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/27 01:23:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static t_token	*identify_subs(t_param *param)
{
	++param->i;
	if (ft_isbracket(param))
	{
		param->token->quote |= BRACKET;
		param->token->depth++;
		param->i++;
	}
	else if (ft_isparen(param))
	{
		param->token->quote |= PARENTHESE;
		param->token->depth++;
		param->i++;
	}
	--param->i;
	return (param->token);
}

t_token			*handle_subs(t_param *param, t_call *token)
{
	param->token->tail = param->i;
	if (param->token->type == UNDEFINED)
		param->token->type = TOKEN;
	else if (param->token->type == OPERATOR)
		param->token = token[OPERATOR].identifier(param);
	if (param->buff[param->i] == '$')
		param->token = identify_subs(param);
	else if (param->buff[param->i] == '`')
	{
		if (param->token->quote & BACKQUOTE)
			param->token->quote &= ~BACKQUOTE;
		else
			param->token->quote |= BACKQUOTE;
	}
	return (param->token);
}
