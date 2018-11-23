/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:30:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/23 09:13:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "reserved_words.h"
#include "libft.h"

static size_t	ionumber_type(const char *buff, size_t start, size_t end)
{
	size_t		i;

	i = end - 1;
	while (i > start && ft_isdigit(buff[i]))
		i--;
	if (i != end - 1)
		return (IO_NUMBER);
	return (WORD);
}

static size_t	reserved_type(const char *buff, size_t start, size_t end)
{
	static t_ope	reserved[] = {
		IF, THEN, ELSE, ELIF, FI, DO, DONE, CASE, ESAC, WHILE, UNTIL, FOR };
	size_t			i;
	size_t			j;

	i = end - 1;
	while (i > start && !ft_isspace(buff[i]))
		i--;
	if (i == start && ft_isspace(buff[i]))
		i++;
	j = 0;
	while (j < sizeof(reserved) / sizeof(reserved[0]))
	{
		if (!ft_strncmp(reserved[j].name, buff + i, end - i))
			return (RESERVED_WORD);
		j++;
	}
	return (WORD);
}

t_token			*identify_token(t_token *token, const char *buff, size_t pos)
{
	token->tail = pos;
	if (token->type & TOKEN)
	{
		if (buff[pos] == '<' || buff[pos] == '>')
			token->type = ionumber_type(buff, token->head, token->tail);
		else
			token->type = reserved_type(buff, token->head, token->tail);
	}
	token->next = new_token(buff[pos], pos);
	return (token->next);
}
