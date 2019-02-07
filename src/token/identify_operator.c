/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 00:38:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/07 00:15:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "operator_types.h"

static size_t	max(size_t a, size_t b)
{
	return ((a > b) ? a : b);
}

size_t		check_operator(t_token *token, size_t len)
{
	static t_ope	ope[] = {
		OP_OR_IF, OP_PIPE, OP_PIPE_AND, OP_NOT, OP_AND_IF, OP_BACKGRND, OP_SEMI,
		OP_DSEMI, OP_LESS, OP_LESSAND, OP_LESS_GREAT, OP_GREAT, OP_GREAT_PIPE,
		OP_AND_GREAT, OP_GREAT_AND, OP_DGREAT, OP_AND_DGREAT, OP_DLESS,
	};
	size_t			i;
	size_t			size;

	i = 0;
	while (i < sizeof(ope) / sizeof(ope[0]))
	{
		size = max(ft_strlen(ope[i].name), len);
		if (!ft_strncmp(ope[i].name, token->head, size))
			return (ope[i].value);
		i++;
	}
	return (0);
}

t_token			*identify_operator(t_param *param)
{
	param->token->len = (param->buff + param->i) - param->token->head;
	param->token->id = check_operator(param->token, param->token->len);
	param->token->next = new_token(param->buff, param->i);
	param->token->next->prev = param->token;
	return (param->token->next);
}
