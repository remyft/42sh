/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 21:08:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 18:32:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "shell_env.h"
#include "operator_types.h"
#include "builtin_alias.h"

static void		alias_new_tokens(t_param *param, t_token *save)
{
	while (param->token->next)
	{
		param->token->alias = "";
		param->token->alen = 0;
		param->token = param->token->next;
	}
	param->token->alias = "";
	param->token->alen = 0;
	if (param->token->quote)
	{
		param->token->alias = param->line + param->i;
		param->token->alen = param->line + param->i - save->head;
	}
}

t_token			*handle_alias(t_param *param, t_s_env *e)
{
	t_alias		*alias;
	t_token		*save;

	alias = alias_get(param->token->head, param->token->len, e->alias_list);
	if (!alias)
		return (param->token);
	save = param->token;
	alias->in_use = 1;
	e->checkquote = 0;
	param->token = tokenise(&alias->value, e);
	e->checkquote = 1;
	alias->in_use = 0;
	if (save->prev)
		save->prev->next = param->token;
	else
		param->head = param->token;
	if (param->token)
		alias_new_tokens(param, save);
	free(save);
	return (param->token);
}
