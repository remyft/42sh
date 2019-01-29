/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:20:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/29 12:58:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "token.h"

static t_token	*check_head(t_token *head)
{
	if (head && head->type == UNDEFINED)
	{
		free(head);
		return (NULLTOKEN);
	}
	return (head);
}

static t_token	*get_tokens(t_param *param, t_call *token)
{
	static t_func	character[] = {
		CHAR_QUOTE, CHAR_CMD, CHAR_SUBS, CHAR_COMMENT, CHAR_NEWLINE, CHAR_EQUAL,
		CHAR_MINUS, CHAR_OPERATOR, CHAR_WORD,
	};
	size_t			i;
	size_t			size;

	i = 0;
	size = (param->token->quote) ? 3 : sizeof(character) / sizeof(*character);
	if (param->token->type == UNDEFINED)
		param->token->head = param->buff + param->i;
	while (i < size)
	{
		if (character[i].is(param->buff[param->i]))
			return (character[i].handler(param, token));
		i++;
	}
	if (!param->token->quote && param->token->type != UNDEFINED)
		return (token[param->token->type].identifier(param));
	return (param->token);
}

t_token			*token_loop(t_param *param, int (*ft_end)(t_param *))
{
	static t_call	token[] = {
		ID_TOKEN, ID_OPERATOR,
	};
	t_token			*head;

	head = param->token;
	while (param->token)
	{
		if (ft_isnull(param) || ft_end(param))
			param->token = handle_end_of_input(param, token);
		else if (ft_end != ft_isnameend && param->token->id == COMMENT)
		{
			if (ft_isendl(param))
				param->token = token[param->token->type].identifier(param);
		}
		else
			param->token = get_tokens(param, token);
		param->i++;
	}
	debug_tokens(head);
	return (check_head(head));
}

t_token			*tokenise(const char *buff)
{
	t_param		param;

	param.token = new_token(buff, 0);
	param.buff = buff;
	param.i = 0;
	return (token_loop(&param, ft_isnull));
}