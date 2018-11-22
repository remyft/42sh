/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:20:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/22 05:27:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "token.h"

static size_t	define_token(const char c)
{
	if (ft_strchr(OPERATORS, c))
		return (OPERATOR);
	else if (c == '\n')
		return (NEWLINE);
	else if (ft_isspace(c))
		return (NEW_INPUT);
	return (TOKEN);
}

static t_token	*new_token(const char c, size_t pos)
{
	t_token		*new;

	new = malloc(sizeof(*new));
	if (new == (t_token *)0)
		return ((t_token *)0);
	new->quoted = 0;
	new->type = define_token(c);
	new->head = pos;
	new->tail = pos;
	new->next = (t_token *)0;
	return (new);
}

static t_token	*end_of_token(t_token *token, const char c, size_t pos)
{
	token->tail = pos;
	if (!(token->type & NEW_INPUT))
	{
		token->next = new_token(c, pos);
		return (token->next);
	}
	token->type = define_token(c);
	return (token);
}

static t_token	*identify_token(t_token *token, const char *buff, size_t pos)
{
	size_t		i;

	if (ft_strchr(OPERATORS, buff[pos]))
	{
		i = token->head;
		printf("OK\n");
		while (i < token->tail && (ft_isspace(buff[i]) || ft_isdigit(buff[i])))
			i++;
		if (i == token->tail)
			token->type = IO_NUMBER;
	}
	token->tail = pos;
	token->next = new_token(buff[pos], pos);
	return (token->next);
}

static t_token	*identify_operator(t_token *token, const char *buff, size_t i)
{
	// static t_ope	ope[] = {
	// 	{ }
	// };

	token->tail = i;
	token->next = new_token(buff[i], i);
	return (token->next);
}

static size_t	tokenize(t_token **tail, const char *buff, size_t i)
{
	if (buff[i] == '\\')
		return (i + 1);
	else if ((buff[i] == '\'' || buff[i] == '"'))
	{
		(*tail)->quoted = buff[i];
		(*tail)->type = TOKEN;
		(*tail)->head = i + 1;
	}
	else if (!ft_isspace(buff[i]) || buff[i] == '\n')
	{
		if ((*tail)->type & NEW_INPUT)
			(*tail)->type = define_token(buff[i]);
		if (buff[i] == '\n')
			*tail = end_of_token(*tail, buff[i], i);
		else if (ft_strchr(OPERATORS, buff[i]))
		{
			if (!((*tail)->type & OPERATOR))
				*tail = end_of_token(*tail, buff[i], i);
		}
		else if ((*tail)->type & OPERATOR)
			*tail = identify_operator(*tail, buff, i);
	}
	else if (!((*tail)->type & NEW_INPUT))
		*tail = identify_token(*tail, buff, i);
	return (i);
}

t_token			*get_tokens(const char *buff, size_t i)
{
	t_token		*head;
	t_token		*tail;

	if ((head = new_token(buff[0], 0)) == (t_token *)0)
		return ((t_token *)0);
	tail = head;
	while (tail && buff[i] && buff[i] != '#')
	{
		if (!tail->quoted)
			i = tokenize(&tail, buff, i);
		else if (tail->quoted && buff[i] == tail->quoted)
			if ((tail = end_of_token(tail, buff[i + 1], i)))
				tail->head++;
		i++;
	}
	if (tail)
		tail->tail = i;
	return (head);
}
