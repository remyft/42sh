/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:30:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/17 23:28:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_alias.h"
#include "grammar_rules.h"
#include "reserved_words.h"

static int		ionumber_type(t_token *token)
{
	size_t		i;

	i = 0;
	while (i < token->len && ft_isdigit(token->head[i]))
		i++;
	return ((i == token->len) ? IO_NUMBER : WORD);
}

static int		reserved_type(t_token *token)
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
		if ((len = ft_strlen(reserve[i].name)) < token->len)
			len = token->len;
		if (!ft_strncmp(reserve[i].name, token->head, len))
			return (RESERVED_WORD);
		i++;
	}
	return (WORD);
}

static int		name_type(t_token *token)
{
	size_t		i;

	i = 0;
	if (ft_isdigit(token->head[i]))
		return (WORD);
	while (i < token->len && ft_isname(token->head[i]))
		i++;
	return ((i == token->len) ? NAME : WORD);
}

t_token			*identify_word(t_param *param)
{
	param->token->len = (param->buff + param->i) - param->token->head;
	if (ft_isquote(*param->token->head))
		param->token->id = WORD;
	else if (param->token->id == COMMENT)
		return (param->token);
	else if (param->token->id == WORD
			&& (param->token->id = reserved_type(param->token)) == WORD)
	{
		if (param->buff[param->i] == '<' || param->buff[param->i] == '>')
			param->token->id = ionumber_type(param->token);
		else
			param->token->id = name_type(param->token);
		param->token = handle_alias(param, param->e);
	}
	param->token->next = new_token(param->buff, param->i);
	param->token->next->prev = param->token;
	return (param->token->next);
}
