/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:36:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/12 18:56:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token_error.h"
#include "token.h"

static t_token	*backslash(t_param *param, int type)
{
	int			qtype;

	qtype = quote_type(param->token->quote);
	if (qtype == SINGLE_QUOTE)
		return (param->token);
	if (!quote_add(&param->token->quote, type))
		return (token_error(ERR_MALLOC, param));
	return (param->token);
}

static t_token	*singlequote(t_param *param, int type)
{
	int			qtype;

	qtype = quote_type(param->token->quote);
	if (qtype == DOUBLE_QUOTE || qtype == BACKQUOTE)
		return (param->token);
	if (qtype == type)
		quote_remove(&param->token->quote, type);
	else if (!quote_add(&param->token->quote, type))
		return (token_error(ERR_MALLOC, param));
	return (param->token);
}

static t_token	*doublequote(t_param *param, int type)
{
	int			qtype;

	qtype = quote_type(param->token->quote);
	if (qtype == SINGLE_QUOTE || qtype == BACKQUOTE)
		return (param->token);
	if (qtype == type)
		quote_remove(&param->token->quote, type);
	else if (!quote_add(&param->token->quote, type))
		return (token_error(ERR_MALLOC, param));
	return (param->token);
}

static t_token	*braceopen(t_param *param, int type)
{
	if (quote_type(param->token->quote) == SINGLE_QUOTE)
		return (param->token);
	if (!quote_add(&param->token->quote, type))
		return (token_error(ERR_MALLOC, param));
	return (param->token);
}

static t_token	*braceclose(t_param *param, int type)
{
	if (!param->token->quote)
		return (param->token);
	quote_remove(&param->token->quote, type);
	return (param->token);
}

static t_token	*parentheseopen(t_param *param, int type)
{
	if (quote_type(param->token->quote) == SINGLE_QUOTE)
		return (param->token);
	if (!quote_add(&param->token->quote, type))
		return (token_error(ERR_MALLOC, param));
	return (param->token);
}

static t_token	*parentheseclose(t_param *param, int type)
{
	if (!param->token->quote)
		return (param->token);
	quote_remove(&param->token->quote, type);
	return (param->token);
}

static t_token	*backquote(t_param *param, int type)
{
	int			qtype;

	qtype = quote_type(param->token->quote);
	if (qtype == SINGLE_QUOTE)
		return (param->token);
	if (qtype == BACKQUOTE)
		quote_remove(&param->token->quote, type);
	else if (!quote_add(&param->token->quote, type))
		return (NULLTOKEN);
	return (param->token);
}

t_token			*handle_quote(t_param *param, t_call *token)
{
	static t_quote_h	quote[] = {
		{ '\\', backslash, BACKSLASH },
		{ '"', doublequote, DOUBLE_QUOTE },
		{ '\'', singlequote, SINGLE_QUOTE },
		{ '{', braceopen, BRACE },
		{ '}', braceclose, BRACE },
		{ '(', parentheseopen, PARENTHESE },
		{ ')', parentheseclose, PARENTHESE },
		{ '`', backquote, BACKQUOTE },
	};
	size_t				i;

	i = 0;
	if (param->token->type == UNDEFINED)
		param->token->type = TOKEN;
	else if (param->token->type == OPERATOR)
		param->token = token[OPERATOR].identifier(param);
	while (i < sizeof(quote) / sizeof(*quote))
	{
		if (param->line[param->i] == quote[i].value)
			return (quote[i].handler(param, quote[i].type));
		i++;
	}
	return (param->token);
}
