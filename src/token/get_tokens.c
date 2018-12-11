/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:20:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/11 14:42:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "token.h"

static t_token	*check_head(t_token *head)
{
	if (head->type == UNDEFINED)
	{
		free(head);
		return (NULLTOKEN);
	}
	return (head);
}

static t_token	*get_tokens(t_param *param, t_call *token)
{
	static t_func	character[] = {
		CHAR_SUBS, CHAR_QUOTE, CHAR_COMMENT, CHAR_NEWLINE, CHAR_OPERATOR,
		CHAR_WORD
	};
	size_t			i;
	size_t			size;

	i = 0;
	size = (param->token->quote) ? 2 : sizeof(character) / sizeof(*character);
	if (param->token->type == UNDEFINED)
		param->token->head = param->i;
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

t_token			*tokenise(const char *buff, size_t i,
							int (*ft_end)(const char *), size_t depth)
{
	static t_call	token[] = {
		ID_TOKEN, ID_OPERATOR,
	};
	t_token			*head;
	t_param			param;

	head = new_token(buff[i], i);
	param.token = head;
	param.buff = buff;
	param.i = i;
	param.depth = depth;
	while (param.token)
	{
		if ((ft_end(param.buff + param.i) && --depth == 0)
			|| ft_isnull(param.buff + param.i))
			param.token = handle_end_of_input(&param, token);
		else if (ft_end != ft_isnameend && param.token->spec == COMMENT)
		{
			if (ft_isendl(param.buff + param.i))
				param.token = token[param.token->type].identifier(&param);
		}
		else
			param.token = get_tokens(&param, token);
		param.i++;
	}
	return (check_head(head));
}
