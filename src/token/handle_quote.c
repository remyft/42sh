/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:36:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/05 20:47:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static t_token	*backslash(t_param *param)
{
	if (!param->buff[param->i + 1])
	{
		ft_putendl("REMY I NEED YOU TO DO THIS WITH ME");
		return (param->token);
	}
	if (!(param->token->quoted & SINGLE_QUOTE))
		param->i++;
	return (param->token);
}

static t_token	*singlequote(t_param *param)
{
	if (param->token->quoted & DOUBLE_QUOTE)
		return (param->token);
	if (!(param->token->quoted & SINGLE_QUOTE))
		param->token->quoted |= SINGLE_QUOTE;
	else
		param->token->quoted &= ~SINGLE_QUOTE;
	return (param->token);
}

static t_token	*doublequote(t_param *param)
{
	// // if a doublequote is in a singlequote don't add doublequote to the quote list
	// if (quote_check(param->token->quote, DOUBLE_QUOTE))
	// 	return (param->token);
	if (param->token->quoted & SINGLE_QUOTE)
		return (param->token);
	if (!(param->token->quoted & DOUBLE_QUOTE))
		param->token->quoted |= DOUBLE_QUOTE;
	else
		param->token->quoted &= ~DOUBLE_QUOTE;
	return (param->token);
}

t_token			*handle_quote(t_param *param, t_call *token)
{
	static t_quote_h	quote[] = {
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
