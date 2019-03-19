/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handlers1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:09:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/16 18:13:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_error.h"

t_token			*backslash(t_param *param, int type)
{
	int			qtype;

	qtype = quote_type(param->token->quote);
	if (qtype == SINGLE_QUOTE)
		return (param->token);
	if (!quote_add(&param->token->quote, type))
		return (token_error(ERR_MALLOC, param));
	return (param->token);
}

t_token			*singlequote(t_param *param, int type)
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

t_token			*doublequote(t_param *param, int type)
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

t_token			*braceopen(t_param *param, int type)
{
	if (quote_type(param->token->quote) == SINGLE_QUOTE)
		return (param->token);
	if (!quote_add(&param->token->quote, type))
		return (token_error(ERR_MALLOC, param));
	return (param->token);
}

t_token			*braceclose(t_param *param, int type)
{
	if (!param->token->quote)
		return (param->token);
	quote_remove(&param->token->quote, type);
	return (param->token);
}
