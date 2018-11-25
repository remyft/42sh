/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:20:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/26 00:55:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "token.h"

static t_token	*end_of_input(t_token *token, const char *buff, size_t pos)
{
	if (token->type & NEW_INPUT)
	{
		token->head = pos;
		token->tail = pos + 1;
		token->type = NEWLINE;
		return (token);
	}
	if (token->type & TOKEN)
		return (identify_token(token, buff, pos));
	if (token->type & OPERATOR)
		return (identify_operator(token, buff, pos));
	token->tail = pos;
	token->next = new_token(buff[pos], pos);
	return (end_of_input(token->next, buff, pos));
}

static t_token	*end_of_token(t_token *token, const char *buff, size_t pos)
{
	token->tail = pos;
	if (token->type & NEW_INPUT)
	{
		token->type = (buff[pos] == '\n') ?
			define_token(buff[pos]) : define_token(buff[pos + 1]);
		return (token);
	}
	token->next = (buff[pos] == '\n') ?
		identify_token(token, buff, pos) : new_token(buff[pos + 1], pos + 1);
	return (token->next);
}

static size_t	tokenize(t_token **tail, const char *buff, size_t i)
{
	if (buff[i] == '\n')
		*tail = end_of_input(*tail, buff, i);
	else if (ft_strchr(OPERATORS, buff[i]))
		*tail = operator_handler(*tail, buff, i);
	else if (!ft_isspace(buff[i]))
		*tail = word_handler(*tail, buff, i);
	else if (buff[i] == '\\')
		return (backslash_handler(buff, i));
	else if ((buff[i] == '\'' || buff[i] == '"'))
	{
		(*tail)->quoted = buff[i];
		(*tail)->type = TOKEN;
		(*tail)->head = i + 1;
	}
	else if ((*tail)->type & TOKEN)
		*tail = identify_token(*tail, buff, i);
	else if ((*tail)->type & OPERATOR)
		*tail = identify_operator(*tail, buff, i);
	return (i);
}

t_token			*get_tokens(const char *buff)
{
	t_token		*head;
	t_token		*tail;
	size_t		i;

	head = new_token(buff[0], 0);
	tail = head;
	i = 0;
	while (buff[i] && buff[i] != '#')
	{
		if (!tail)
			return (head);
		if (!tail->quoted)
			i = tokenize(&tail, buff, i);
		else if (tail->quoted && buff[i] == tail->quoted)
			if ((tail = end_of_token(tail, buff, i)))
				tail->head++;
		i++;
	}
	if (tail)
	{
		tail->tail = i;
		if (tail->type & NEW_INPUT)
			tail->type = NEWLINE;
	}
	return (head);
}
