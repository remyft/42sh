/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 19:23:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/27 03:12:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

static t_token	*backslsh_handler(t_token *token, const char *buff, size_t *pos)
{
	if (buff[*pos + 1] == '\n')
		ft_strcpy((char *)buff + *pos, (char *)buff + *pos + 2);
	else
		*pos = *pos + 2;
	return (token);
}

static t_token	*squote_handler(t_token *token, const char *buff, size_t *pos)
{
	if (!token->quoted)
	{
		if (token->type & TOKEN)
			token = identify_token(token, buff, pos);
		else if (token->type & OPERATOR)
			token = identify_operator(token, buff, pos);
		token->quoted = buff[*pos];
		token->type = TOKEN;
		token->spec = WORD;
		token->head = *pos + 1;
	}
	else if (token->quoted == buff[*pos])
	{
		token->tail = *pos;
		token->next = new_token(buff[*pos + 1], *pos + 1);
		token = token->next;
	}
	return (token);
}

static t_token	*dquote_handler(t_token *token, const char *buff, size_t *pos)
{
	if (!token->quoted)
	{
		if (token->type & TOKEN)
			token = identify_token(token, buff, pos);
		else if (token->type & OPERATOR)
			token = identify_operator(token, buff, pos);
		token->quoted = buff[*pos];
		token->type = TOKEN;
		token->spec = WORD;
		token->head = *pos + 1;
	}
	else if (token->quoted == buff[*pos])
	{
		token->tail = *pos;
		token->next = new_token(buff[*pos + 1], *pos + 1);
		token = token->next;
	}
	return (token);
}

t_token			*quote_handler(t_token *token, const char *buff, size_t *pos)
{
	if (buff[*pos] == '\\')
		return (backslsh_handler(token, buff, pos));
	if (buff[*pos] == '\'')
		return (squote_handler(token, buff, pos));
	if (buff[*pos] == '"')
		return (dquote_handler(token, buff, pos));
	return (token);
}
