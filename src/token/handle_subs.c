/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:35:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/01 03:11:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static t_token	*arithmetic_expansion(t_param *param)
{
	return (param->token);
}

static t_token	*parameter_expansion(t_param *param)
{
	return (param->token);
}

static t_token	*handle_dollar_sign(t_param *param)
{
	if (!ft_strncmp(param->buff + param->i + 1, "((", 2))
		arithmetic_expansion(param);
	else if (param->buff[param->i + 1] == '{'
			|| param->buff[param->i + 1] == '('
			|| !ft_isnull(param->buff[param->i + 1])
			|| !ft_isquote(param->buff[param->i + 1])
			|| param->buff[param->i + 1] != '`'
			|| !ft_isoperator(param->buff[param->i + 1]))
		parameter_expansion(param);
	return (param->token);
}

static t_token	*handle_backquote(t_param *param)
{
	return (param->token);
}

t_token			*handle_subs(t_param *param, t_call *token)
{
	if (param->token->type == UNDEFINED)
		param->token->type = TOKEN;
	else if (param->token->type == OPERATOR)
		param->token = token[OPERATOR].identifier(param);
	if (param->buff[param->i] == '$')
		handle_dollar_sign(param);
	else if (param->buff[param->i] == '`')
		handle_backquote(param);
	return (param->token);
}