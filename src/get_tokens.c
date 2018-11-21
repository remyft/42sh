/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:20:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/21 23:42:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "token.h"

static t_token	*new_token(size_t type, size_t pos)
{
	t_token		*new;

	new = malloc(sizeof(*new));
	if (new == (t_token *)0)
		return ((t_token *)0);
	new->type = type;
	new->head = pos;
	new->tail = pos;
	new->next = (t_token *)0;
	return (new);
}

static void		start_of_token(t_token *token, size_t type, size_t pos)
{
	token->type = type;
	token->head = pos;
	token->tail = pos;
}

static t_token	*end_of_token(t_token *token, size_t type, size_t pos)
{
	token->tail = pos;
	token->next = new_token(type, pos);
	return (token->next);
}

static size_t	tokenize(t_token **tail, const char *buff, size_t i, char *q)
{
	if (*buff == '\\')
		return (i + 1);
	else if ((*buff == '\'' || *buff == '"'))
	{
		*q = *buff;
		start_of_token(*tail, WORD, i);
	}
	else if (!ft_isspace(*buff) || *buff == '\n')
	{
		if ((*tail)->type & END_OF_INPUT)
			start_of_token(*tail,
			(ft_strchr(OPERATORS, *buff)) ? OPERATOR : WORD, i);
		if (ft_strchr(OPERATORS, *buff) ||
			(*buff == '-' && (*tail)->type & OPERATOR))
		{
			if ((*tail)->type & WORD)
				*tail = end_of_token(*tail, OPERATOR, i);
		}
		else if ((*tail)->type & OPERATOR)
			*tail = end_of_token(*tail, WORD, i);
	}
	else if (!((*tail)->type & END_OF_INPUT))
		*tail = end_of_token(*tail, END_OF_INPUT, i);
	return (i);
}

t_token			*get_tokens(const char *buff, size_t i, char quoted)
{
	t_token		*head;
	t_token		*tail;

	if ((head = new_token(END_OF_INPUT, 0)) == (t_token *)0)
		return ((t_token *)0);
	tail = head;
	while (tail && buff[i] && buff[i] != '#')
	{
		if (!quoted)
			i = tokenize(&tail, buff + i, i, &quoted);
		else if (quoted && buff[i] == quoted)
		{
			quoted = 0;
			tail = end_of_token(tail, END_OF_INPUT, i + 1);
		}
		i++;
	}
	if (tail)
		tail->tail = i;
	return (head);
}
