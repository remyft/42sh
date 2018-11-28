/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 01:56:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/28 06:40:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static int		dollar_special(int c)
{
	return ((c == '$') || (c == '}') || (c == ')'));
}

static t_token	*dollar_expansion(t_token *token, const char *buff, size_t *pos)
{
	size_t		len;

	(*pos)++;
	while (buff[*pos]
		&& !ft_isspace(buff[*pos])
		&& !ft_isoperator(buff[*pos])
		&& !ft_isquote(buff[*pos])
		&& !ft_isexpansion(buff[*pos])
		&& !dollar_special(buff[*pos]))
		(*pos)++;
	token->tail = *pos;
	len = (dollar_special(buff[*pos])) ? *pos + 1 : *pos;
	return (identify_operator(token, buff, &len));
}

static t_token	*backquote_handler(t_token *tok, const char *buff, size_t *pos)
{
	(void)tok;
	(void)buff;
	(void)pos;
	return (token);
}

t_token			*expansion_handler(t_token *tok, const char *buff, size_t *pos)
{
	if (buff[*pos] == '$')
		return (dollar_handler(tok, buff, pos));
	if (buff[*pos] == '`')
		return (backquote_handler(tok, buff, pos));
	return (tok);
}