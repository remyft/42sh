/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_grouped_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:42:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/06 15:39:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static t_token	*parent(t_param *param)
{
	// if (param->token->quote && param->token->quote != PARENTHESE)
	// 	return (param->token);
	// param->token->quote |= PARENTHESE;
	// param->token->depth++;
	// return (param->token);

	// if the parenthese is quoted do nothing
	if (param->token->quoted)
		return (param->token);
	// Add parenthese to the quote list
	if (!quote_add(&param->token->quote, PARENTHESE))
		return (NULLTOKEN);
	return (param->token);
}

static t_token	*parentend(t_param *param)
{
	if (!param->token->quote)
		return (param->token);
	quote_remove(&param->token->quote, PARENTHESE);
	return (param->token);
}

t_token			*handle_grouped_command(t_param *param, t_call *token)
{
	static t_quote_h	quote[] = {
		{ '(', parent },
		{ ')', parentend },
	};
	size_t				i;

	i = 0;
	if (param->token->type == UNDEFINED)
		param->token->type = TOKEN;
	else if (param->token->type != TOKEN)
		param->token = token[OPERATOR].identifier(param);
	while (i < sizeof(quote) / sizeof(*quote))
	{
		if (param->buff[param->i] == quote[i].value)
			return (quote[i].handler(param));
		i++;
	}
	return (param->token);
}
