/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 00:38:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/22 20:25:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "operator_types.h"

static size_t	check_operator(t_token *token, const char *buff, size_t len)
{
	static t_ope	ope[] = {
		OP_OR_IF, OP_PIPE, OP_PIPE_AND, OP_NOT, OP_AND_IF, OP_BACKGRND, OP_SEMI,
		OP_DSEMI, OP_LESS, OP_LESSAND, OP_LESS_GREAT, OP_GREAT, OP_GREAT_PIPE,
		OP_AND_GREAT, OP_GREAT_AND, OP_DGREAT, OP_AND_GREAT, OP_DGREAT_AND,
		OP_DLESS, OP_TLESS,
	};
	size_t			i;

	i = 0;
	while (i < sizeof(ope) / sizeof(ope[0]))
	{
		if (len == ft_strlen(ope[i].name)
			&& !ft_strncmp(buff + token->head, ope[i].name, len))
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
