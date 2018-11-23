/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:20:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/23 03:24:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "token.h"

static t_token	*end_of_token(t_token *token, const char c, size_t pos)
{
	token->tail = pos;
	if (token->type & NEW_INPUT)
	{
		token->type = define_token(c);
		return (token);
	}
	token->next = new_token(c, pos);
	return (token->next);
}

static t_token	*identify_operator(t_token *token, const char *buff, size_t i)
{
	// static t_ope	ope[] = {
	// 	{ "&&", AND_IF },
	// 	{ "||", OR_IF },
	// 	{ ";", SEMI },
	// 	{ ";;", DSEMI },
	// 	{ "<<", DLESS },
	// 	{ ">>", DGREAT },
	// 	{ "<&", LESSAND },
	// 	{ ">&", GREATAND },
	// 	{ "<>", LESSGREAT },
	// 	{ "<<-", DLESSDASH },
	// 	{ ">|", CLOBBER }
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
	else if (!ft_isspace(buff[i]))
	{
		if ((*tail)->type & NEW_INPUT)
			(*tail)->type = define_token(buff[i]);
		if (ft_strchr(OPERATORS, buff[i]))
		{
			if (!((*tail)->type & OPERATOR))
				*tail = identify_token(*tail, buff, i);
		}
		else if ((*tail)->type & OPERATOR)
			*tail = identify_operator(*tail, buff, i);
	}
	else if (buff[i] == '\n' && (!((*tail)->type & NEWLINE)))
		*tail = end_of_token(*tail, buff[i], i);
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
	ft_putstr(buff);
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
