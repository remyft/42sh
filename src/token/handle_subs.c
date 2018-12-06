/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:35:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/06 02:23:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static t_token	*identify_subs(t_param *param)
{
	param->i++;
	if (param->buff[param->i] == '{')
		param->token = get_subs(param, ft_isbracket, 1);
	else if (!ft_strncmp(param->buff + param->i, "((", 2))
		param->token = get_subs(param, ft_isdparen, 2);
	else if (param->buff[param->i] == '(')
		param->token = get_subs(param, ft_isparen, 1);
	else
		param->token = get_subs(param, ft_isnotname, 0);
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
