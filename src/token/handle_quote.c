/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:36:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/11 09:58:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static t_token	*backslash(t_param *param)
{
	if (!(param->token->quote & SINGLE_QUOTE))
		param->i++;
	return (param->token);
}

static t_token	*singlequote(t_param *param)
{
	if (param->token->quote && param->token->quote & ~SINGLE_QUOTE)
		return (param->token);
	if (!param->token->quote)
		param->token->quote |= SINGLE_QUOTE;
	else
		param->token->quote &= ~SINGLE_QUOTE;
	return (param->token);
}

static t_token	*doublequote(t_param *param)
{
	if (param->token->quote && param->token->quote != DOUBLE_QUOTE)
		return (param->token);
	if (!param->token->quote)
		param->token->quote |= DOUBLE_QUOTE;
	else
		param->token->quote &= ~DOUBLE_QUOTE;
	return (param->token);
}

t_token			*handle_quote(t_param *param, t_call *token)
{
	static t_quote	quote[] = {
		{ '\\', backslash },
		{ '\'', singlequote },
		{ '"', doublequote },
	};
	size_t			i;

	i = 0;
	if (param->token->type == UNDEFINED)
		param->token->type = TOKEN;
	else if (param->token->type == OPERATOR)
		param->token = token[OPERATOR].identifier(param);
	while (i < sizeof(quote) / sizeof(*quote))
	{
		if (param->buff[param->i] == quote[i].value)
			return (quote[i].handler(param));
		i++;
	}
	return (param->token);
}
