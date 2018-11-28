/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 00:38:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/28 00:50:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static size_t	check_operator(t_token *token, const char *buff, size_t len)
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
		if (!ft_strncmp(buff + token->head, ope[i].name, len))
			return (ope[i].value);
		i++;
	}
	return (0);
}

t_token			*identify_operator(t_token *tok, const char *buff, size_t *pos)
{
	size_t	ret;

	tok->tail = *pos;
	if (check_operator(tok, buff, *pos - tok->head + 1))
		return (tok);
	if ((ret = check_operator(tok, buff, tok->tail - tok->head)))
		tok->spec = ret;
	tok->next = new_token(buff[*pos], *pos);
	return (tok->next);
}
