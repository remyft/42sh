/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:54:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/27 23:51:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static t_token	*dollar_handler(t_token *token, const char *buff, size_t *pos)
{
	size_t		len;

	(*pos)++;
	while (buff[*pos]
		&& !ft_isspace(buff[*pos])
		&& !ft_isoperator(buff[*pos])
		&& !ft_isquote(buff[*pos])
		&& !ft_isspec(buff[*pos])
		&& printf("char:%c\n", buff[*pos]))
		(*pos)++;
	token->tail = *pos;
	if (buff[*pos] == '$' && buff[*pos - 1] == '$')
	{
		len = *pos + 1;
		return (identify_operator(token, buff, &len));
	}
	return (identify_operator(token, buff, pos));
}

t_token			*word_handler(t_token *token, const char *buff, size_t *pos)
{
	if (token->type & OPERATOR)
		token = identify_operator(token, buff, pos);
	token->tail = *pos;
	token->type = TOKEN;
	if (buff[*pos] == '$')
		token = dollar_handler(token, buff, pos);
	return (token);
}
