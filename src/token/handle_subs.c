/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 02:35:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/13 19:33:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static t_token	*token_end(t_token *token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}

static t_token	*do_subs(t_param *param, int (*ft_end)(t_param *))
{
	t_token		*save;

	save = param->token;
	param->i++;
	param->token = new_token(param->buff[param->i], param->i);
	save->subs = token_loop(param, ft_end);
	param->token = save;
	save = token_end(save->subs);
	param->token->tail = save->tail;
	param->i = save->tail + 1;
	return (param->token);
}

static t_token	*identify_subs(t_param *param)
{
	param->i++;
	if (ft_isbracket(param))
		param->token = do_subs(param, ft_isbracketend);
	else if (ft_isparen(param))
		param->token = do_subs(param, ft_isparenend);
	else
		param->i--;
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
		param->token = do_subs(param, ft_isbackquote);
	return (param->token);
}
