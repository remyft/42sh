/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 21:08:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/17 23:47:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "shell_env.h"
#include "operator_types.h"
#include "builtin_alias.h"

static int		is_command_token(t_token *token)
{
	return (token->type == OPERATOR && token->id < LESS_VALUE);
}

static int		is_valid_alias_name(t_token *token)
{
	size_t		i;

	i = 0;
	while (i < token->len)
		if (token->head[i] != '_' && !ft_isalnum(token->head[i]))
			return (0);
		else
			i++;
	return (1);
}

t_token			*handle_alias(t_param *param, t_s_env *e)
{
	t_alias		*alias;
	t_token		*save;

	if (param->token->prev && (!is_command_token(param->token->prev)
	|| !is_valid_alias_name(param->token)))
		return (param->token);
	alias = alias_get(param->token->head, param->token->len, e->alias_list);
	if (!alias)
		return (param->token);
	alias->in_use = 1;
	save = param->token;
	param->token = tokenise(alias->value, e);
	alias->in_use = 0;
	if (!param->token)
		return (save);
	if (save->prev)
		save->prev->next = param->token;
	else
		param->head = param->token;
	free(save);
	while (param->token->next)
		param->token = param->token->next;
	return (param->token);
}
