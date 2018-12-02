/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:20:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/01 02:29:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "token.h"

static t_token	*tokenize(t_param *param)
{
	static t_func	character[] = {
		CHAR_NULL, CHAR_QUOTE, CHAR_SUBS, CHAR_NEWLINE, CHAR_OPERATOR, CHAR_WORD
	};
	static t_call	token[] = {
		ID_OPERATOR, ID_TOKEN,
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
	if (!param->token->quote && !(param->token->type == UNDEFINED))
		return (token[param->token->type].identifier(param));
	return (param->token);
}

t_token			*get_tokens(const char *buff)
{
	t_token			*head;
	t_param			param;

	head = new_token(buff[0], 0);
	param.token = head;
	param.buff = buff;
	param.i = 0;
	while (param.token)
	{
		param.token = tokenize(&param);
		param.i++;
	}
	for (t_token *ptr = head; ptr; ptr = ptr->next) {
	printf("------------------------------\n"
			"type:%d spec:%d head:%ld tail:%ld quoted:%c\n",
			ptr->type, ptr->spec, ptr->head, ptr->tail, ptr->quote);
	write(1, "command: \"", 10);
	write(1, buff + ptr->head, ptr->tail - ptr->head);
	write(1, "\"\n", 2);
	}
	return (head);
}
