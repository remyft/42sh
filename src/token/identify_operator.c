/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 00:38:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/26 00:54:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

t_token		*identify_operator(t_token *token, const char *buff, size_t pos)
{
	static t_ope	ope[] = {
		OR_IF, PIPE, PIPE_AND, NOT, AND_IF, BACKGRND, SEMI, DSEMI, PAREN_LEFT,
		PAREN_RIGHT, LESS, LESSAND, LESS_GREAT, GREAT, GREAT_PIPE, AND_GREAT,
		GREAT_AND, DGREAT, AND_GREAT, DGREAT_AND, DLESS, TLESS
	};
	size_t			i;

	i = 0;
	while (i < sizeof(ope) / sizeof(ope[0]))
	{
		if (!ft_strncmp(buff + token->head, ope[i].name, pos - token->head + 1))
			return (token);
		i++;
	}
	token->tail = pos;
	while (i < sizeof(ope) / sizeof(ope[0]))
	{
		if (!ft_strncmp(buff + token->head, ope[i].name, token->tail - token->head))
		{
			token->type = ope[i].value;
			break ;
		}
		i++;
	}
	token->next = new_token(buff[pos], pos);
	return (token->next);
}
