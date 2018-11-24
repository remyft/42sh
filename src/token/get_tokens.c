/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:20:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/23 09:14:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "token.h"

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
		identify_token(token, buff, pos) : new_token(buff[pos + 1], pos);
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
	if (buff[i] == '\n' && (!((*tail)->type & NEWLINE)))
		*tail = end_of_token(*tail, buff, i);
	else if (buff[i] == '\\')
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
	else if (!((*tail)->type & NEW_INPUT))
		*tail = identify_token(*tail, buff, i);
	return (i);
}

t_token			*get_tokens(const char *buff, size_t i)
{
	t_token		*head;
	t_token		*tail;

	head = new_token(buff[0], 0);
	tail = head;
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
	tail->tail = i;
	return (head);
}
