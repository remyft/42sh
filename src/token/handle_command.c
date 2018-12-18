/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:42:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/18 18:11:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static t_token	*bracket(t_param *param)
{
	if (param->token->quote && param->token->quote != BRACKET)
		return (param->token);
	param->token->quote |= BRACKET;
	param->token->depth++;
	return (param->token);
}

static t_token	*bracketend(t_param *param)
{
	if (!param->token->quote || param->token->quote & ~BRACKET)
		return (param->token);
	if (--param->token->depth == 0)
		param->token->quote &= ~BRACKET;
	return (param->token);
}

static t_token	*parent(t_param *param)
{
	if (param->token->quote && param->token->quote != PARENTHESE)
		return (param->token);
	param->token->quote |= PARENTHESE;
	param->token->depth++;
	return (param->token);
}

static t_token	*parentend(t_param *param)
{
	if (!param->token->quote || param->token->quote & ~PARENTHESE)
		return (param->token);
	if (--param->token->depth == 0)
		param->token->quote &= ~PARENTHESE;
	return (param->token);
}

t_token			*handle_command(t_param *param, t_call *token)
{
	static t_quote	quote[] = {
		{ '{', bracket },
		{ '}', bracketend },
		{ '(', parent },
		{ ')', parentend },
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
