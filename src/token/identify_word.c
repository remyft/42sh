/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:30:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/19 23:26:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar_rules.h"
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
	static t_ope	reserve[] = {
		TOKEN_IF, TOKEN_THEN, TOKEN_ELSE, TOKEN_ELIF, TOKEN_FI, TOKEN_DO,
		TOKEN_DONE, TOKEN_CASE, TOKEN_ESAC, TOKEN_WHILE, TOKEN_UNTIL, TOKEN_FOR,
	};
	size_t			i;
	size_t			j;
	size_t			len;

	i = param->token->tail - param->token->head;
	j = 0;
	while (j < sizeof(reserve) / sizeof(reserve[0]))
	{
		if ((len = ft_strlen(reserve[j].name)) < i)
			len = i;
		if (!ft_strncmp(reserve[j].name, param->buff + param->token->head, len))
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
		param->token->id = WORD;
	else if (param->token->id == WORD
			&& (param->token->id = reserved_type(param)) == WORD)
	{
		if (param->buff[param->i] == '<' || param->buff[param->i] == '>')
			param->token->id = ionumber_type(param);
		else
			param->token->id = name(param);
	}
	param->token->next = new_token(param->buff[param->i], param->i);
	param->token->next->prev = param->token;
	return (param->token->next);
}
