/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:35:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/06 16:58:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static t_token	*identify_subs(t_param *param)
{
	++param->i;
	if (ft_isbracket(param))
	{
		param->token->quoted |= BRACKET;
		param->token->depth++;
		param->i++;
	}
	else if (ft_isparen(param))
	{
		param->token->quoted |= PARENTHESE;
		param->token->depth++;
		param->i++;
	}
	--param->i;
	return (param->token);
}

t_token			*handle_subs(t_param *param, t_call *token)
{
	if (param->token->type == UNDEFINED)
		param->token->type = TOKEN;
	else if (param->token->type != TOKEN)
		param->token = token[OPERATOR].identifier(param);
	if (param->buff[param->i] == '$')
		param->token = identify_subs(param);
	else if (param->buff[param->i] == '`')
	{
		if (quote_type(param->token->quote) == BACKQUOTE)
			quote_remove(&param->token->quote, BACKQUOTE);
		else if (!quote_add(&param->token->quote, BACKQUOTE))
			return (NULLTOKEN);
	}
	return (param->token);
}
