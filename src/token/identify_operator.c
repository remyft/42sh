/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 00:38:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/11 07:18:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "operator.h"

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

t_token			*identify_operator(t_param *param)
{
	size_t	ret;

	param->token->tail = param->i;
	ret = param->i - param->token->head + 1;
	if (check_operator(param->token, param->buff, ret))
		return (param->token);
	ret = param->token->tail - param->token->head;
	if ((ret = check_operator(param->token, param->buff, ret)))
		param->token->spec = ret;
	param->token->next = new_token(param->buff[param->i], param->i);
	param->token->next->prev = param->token;
	return (param->token->next);
}
