/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:35:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/05 22:34:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

/*
** Problem here if param->token->subs in not NULL.
*/

static t_token	*get_subs(t_param *param, int (*ft_end)(const char *), size_t i)
{
	t_token		*ptr;

	param->token->subs = get_tokens(param->buff, param->i + i, ft_end);
	ptr = param->token->subs;
	while (ptr && ptr->next)
		ptr = ptr->next;
	if (ptr)
	{
		param->token->tail = ptr->tail;
		param->i = ptr->tail;
	}
	return (param->token);
}

static t_token	*identify_subs(t_param *param)
{
	param->i++;
	if (param->buff[param->i] == '{')
		param->token = get_subs(param, ft_isbracket, 1);
	else if (!ft_strncmp(param->buff + param->i, "((", 2))
		param->token = get_subs(param, ft_isdparen, 2);
	else if (param->buff[param->i] == '(')
		param->token = get_subs(param, ft_isparen, 1);
	else if (ft_isname(param->buff[param->i]))
		param->token = get_subs(param, ft_isnotname, 1);
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
