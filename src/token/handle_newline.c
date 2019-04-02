/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_newline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:16:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/02 19:20:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_error.h"
#include "operator_types.h"
#include "parser.h"
#include "command.h"

static t_token	*exec_line(t_param *param)
{
	t_m_list	*tree;

	if (!(tree = parse((char **)&param->line, &param->head, param->e)))
		return (NULLTOKEN);
	execute_list(tree, param->e);
	free_m_list(&tree);
	free_token(&param->head);
	if (!(param->token = new_token(param->line + param->i + 1, 0)))
		return (token_error(ERR_MALLOC, param));
	param->line = param->line + param->i + 1;
	param->i = 0;
	param->head = param->token;
	free_m_list(&tree);
	return (param->token);
}

t_token			*handle_newline(t_param *param, t_call *token)
{
	if (!param->token->prev)
		return (param->token);
	if (param->token->type != UNDEFINED)
	{
		param->token = token[param->token->type].identifier(param);
		if (!(param->token = exec_line(param)))
			free_token(&param->head);
		return (param->token);
	}
	if (param->token->prev->type != OPERATOR
	|| param->token->prev->id != NEWLINE_VALUE)
		param->token->type = OPERATOR;
	return (param->token);
}

