/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:30:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/11 07:18:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "reserved_words.h"
#include "libft.h"

static int		ionumber_type(t_param *param)
{
	size_t		i;

	i = param->token->tail - 1;
	while (i && ft_isdigit(param->buff[i]))
		i--;
	if ((!i && ft_isdigit(param->buff[i])) || i < param->token->head)
		return (IO_NUMBER);
	return (WORD);
}

static int		reserved_type(t_param *param)
{
	static t_ope	reserved[] = {
		IF, THEN, ELSE, ELIF, FI, DO, DONE, CASE, ESAC, WHILE, UNTIL, FOR };
	size_t			i;
	size_t			j;

	i = param->token->tail - 1;
	while (i > param->token->head && !ft_isspace(param->buff[i]))
		i--;
	if (i == param->token->head && ft_isspace(param->buff[i]))
		i++;
	j = 0;
	while (j < sizeof(reserved) / sizeof(reserved[0]))
	{
		if (!ft_strncmp(reserved[j].name, param->buff + i,
						param->token->tail - i))
			return (RESERVED_WORD);
		j++;
	}
	return (WORD);
}

static int		name(t_param *param)
{
	size_t		i;

	i = param->token->head;
	if (ft_isdigit(param->buff[param->token->head]))
		return (WORD);
	while (i < param->token->tail)
	{
		if (!ft_isname(param->buff[i]))
			return (WORD);
		i++;
	}
	return (NAME);
}

t_token			*identify_word(t_param *param)
{
	param->token->tail = param->i;
	if (ft_isquote(param->buff[param->token->head]))
		param->token->spec = WORD;
	else if ((param->token->spec = reserved_type(param)) == WORD)
	{
		if (param->buff[param->i] == '<' || param->buff[param->i] == '>')
			param->token->spec = ionumber_type(param);
		else
			param->token->spec = name(param);
	}
	if (param->token->spec == WORD || param->token->spec == NAME)
		param->token->command = expand_word(param->buff, param->token);
	param->token->next = new_token(param->buff[param->i], param->i);
	param->token->next->prev = param->token;
	return (param->token->next);
}
