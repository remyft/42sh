/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:35:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/11 14:33:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static t_token	*identify_subs(t_param *param)
{
	param->i++;
	if (ft_isbracket(param->buff + param->i))
	{
		param->token->quote |= BRACKET;
		param->depth++;
		param->token = get_subs(param, ft_isbracketend, 1);
		param->depth--;
		param->token->quote &= ~BRACKET;
	}
	else if (ft_isparen(param->buff + param->i))
	{
		param->token->quote |= BRACKET;
		param->depth++;
		param->token = get_subs(param, ft_isparenend, 1);
		param->depth--;
		param->token->quote &= ~BRACKET;
	}
	else
		param->token = get_subs(param, ft_isnameend, 0);
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
		param->token = get_subs(param, ft_isbackquote, 1);
	return (param->token);
}
