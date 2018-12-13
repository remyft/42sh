/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:35:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/13 17:43:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static t_token	*identify_subs(t_param *param)
{
	t_token		*save;

	param->i++;
	if (ft_isbracket(param))
	{
		save = param->token;
		param->i++;
		param->token = new_token(param->buff[param->i], param->i);
		save->subs = token_loop(param, ft_isbracketend);
		save->subs->quote &= ~BRACKET;
		save->tail = save->subs->tail;
		param->token = save;
		param->i = save->tail + 1;
	}
	else if (ft_isparen(param))
	{
		save = param->token;
		param->i++;
		param->token = new_token(param->buff[param->i], param->i);
		save->subs = token_loop(param, ft_isparenend);
		save->subs->quote &= ~PARENTHESE;
		save->tail = save->subs->tail;
		param->token = save;
		param->i = save->tail + 1;
	}
	else
		param->i--;
	// else
	// {
	// 	param->token = token_loop(param, ft_isnameend);
	// }
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
			param->token->quote |= BACKSLASH;
		else
			param->token->quote &= ~BACKSLASH;
		if (param->token->quote & BACKSLASH)
			token_loop(param, ft_isbackquote);
	}
	return (param->token);
}
