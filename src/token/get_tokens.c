/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:20:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/27 03:12:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "token.h"

static t_token	*end_of_input(t_token *token, const char *buff, size_t *pos)
{
	if (token->type & TOKEN)
		return (end_of_input(identify_token(token, buff, pos), buff, pos));
	if (token->type & OPERATOR)
		return (end_of_input(identify_operator(token, buff, pos), buff, pos));
	token->tail = *pos + 1;
	token->spec = NEWLINE;
	return (token);
}

static t_token	*tokenize(t_token *tail, const char *buff, size_t *pos)
{
	static t_func	tokens[] = {
		CHAR_QUOTE, CHAR_NEWLINE, CHAR_OPERATOR, CHAR_WORD,
	};
	static t_id		id[] = {
		ID_TOKEN, ID_OPERATOR,
	};
	size_t			i;

	i = 0;
	if (tail->type & UNDEFINED)
		tail->head = *pos;
	while (i < sizeof(tokens) / sizeof(tokens[0]))
	{
		if (tokens[i].is(buff[*pos]))
			return (tokens[i].exec(tail, buff, pos));
		i++;
	}
	i = 0;
	while (i < sizeof(id) / sizeof(id[0]))
	{
		if (tail->type & id[i].type)
			return (id[i].exec(tail, buff, pos));
		i++;
	}
	return (tail);
}

t_token			*get_tokens(const char *buff)
{
	t_token			*head;
	t_token			*tail;
	size_t			i;

	head = new_token(buff[0], 0);
	tail = head;
	i = 0;
	while (tail && buff[i])
	{
		if (!tail->quoted || tail->quoted == buff[i])
		{
			if (buff[i] == '#')
			{
				tail = end_of_input(tail, buff, &i);
				break ;
			}
			tail = tokenize(tail, buff, &i);
		}
		i++;
	}
	return (head);
}
