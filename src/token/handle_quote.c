/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:36:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/01 00:40:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static void		handle_backslash(t_param *param)
{
	char		*ptr;

	ptr = (char *)param->buff + param->i;
	if (*(ptr + 1) == '\n')
	{
		ft_strcpy(ptr, ptr + 2);
		param->i--;
	}
	else
		param->token->quote |= BACKSLASH;
}

static void		handle_squote(t_param *param)
{
	if (param->token->quote && !(param->token->quote & SINGLE_QUOTE))
		return ;
	if (!param->token->quote)
		param->token->quote |= SINGLE_QUOTE;
	else
		param->token->quote &= ~SINGLE_QUOTE;
}

static void		handle_dquote(t_param *param)
{
	if (param->token->quote && !(param->token->quote & DOUBLE_QUOTE))
		return ;
	if (!param->token->quote)
		param->token->quote |= DOUBLE_QUOTE;
	else
		param->token->quote &= ~DOUBLE_QUOTE;
}

t_token			*handle_quote(t_param *param, t_call *token)
{
	if (param->token->type == UNDEFINED)
		param->token->type = TOKEN;
	else if (param->token->type == OPERATOR)
		param->token = token[OPERATOR].identifier(param);
	if (param->buff[param->i] == '\\')
		handle_backslash(param);
	else if (param->buff[param->i] == '\'')
		handle_squote(param);
	else if (param->buff[param->i] == '"')
		handle_dquote(param);
	return (param->token);
}