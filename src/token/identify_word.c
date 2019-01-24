/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:30:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/24 00:10:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar_rules.h"
#include "reserved_words.h"
#include "libft.h"

static int		ionumber_type(t_param *param)
{
	size_t		i;

	i = 0;
	while (i < param->token->len && ft_isdigit(param->token->head[i]))
		i++;
	return ((i == param->token->len) ? IO_NUMBER : WORD);
}

static int		reserved_type(t_param *param)
{
	static t_ope	reserve[] = {
		TOKEN_IF, TOKEN_THEN, TOKEN_ELSE, TOKEN_ELIF, TOKEN_FI, TOKEN_DO,
		TOKEN_DONE, TOKEN_CASE, TOKEN_ESAC, TOKEN_WHILE, TOKEN_UNTIL, TOKEN_FOR,
	};
	size_t			i;
	size_t			len;

	i = 0;
	while (i < sizeof(reserve) / sizeof(reserve[0]))
	{
		if ((len = ft_strlen(reserve[i].name)) < param->token->len)
			len = param->token->len;
		if (!ft_strncmp(reserve[i].name, param->token->head, len))
			return (RESERVED_WORD);
		i++;
	}
	return (WORD);
}

static int		name(t_param *param)
{
	size_t		i;

	i = 0;
	if (ft_isdigit(param->token->head[i]))
		return (WORD);
	while (i < param->token->len && ft_isname(param->token->head[i]))
		i++;
	return ((i == param->token->len) ? NAME : WORD);
}

t_token			*identify_word(t_param *param)
{
	param->token->len = (param->buff + param->i) - param->token->head;
	if (ft_isquote(*param->token->head))
		param->token->id = WORD;
	else if (param->token->id == COMMENT)
		return (param->token);
	else if (param->token->id == WORD
			&& (param->token->id = reserved_type(param)) == WORD)
	{
		if (param->buff[param->i] == '<' || param->buff[param->i] == '>')
			param->token->id = ionumber_type(param);
		else
			param->token->id = name(param);
	}
	param->token->next = new_token(param->buff, param->i);
	param->token->next->prev = param->token;
	return (param->token->next);
}
