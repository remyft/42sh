/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 12:00:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/04 23:55:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_loop.h"
#include "expansion_errors.h"

static int		expand_loop(t_ret *ret, t_exp *param, int (*end_loop)(t_exp *))
{
	static t_e_character	character[] = {
		OP_EXP_NULL, OP_EXP_BACKSLSH, OP_EXP_SQUOTE, OP_EXP_DQUOTE,
		OP_EXP_TILDE, OP_EXP_DOLLAR, OP_EXP_BACKTICK, OP_EXP_STAR,
		OP_EXP_BRACKET, OP_EXP_QUESTION,
	};
	size_t					i;
	int						error;

	error = ERR_NONE;
	while (param->i < param->buff_len && end_loop(param))
	{
		i = (param->expand) ? sizeof(character) / sizeof(character[0]) - 1 : 3;
		while (i > 0)
		{
			if (param->buff[param->i] == character[i].value)
				break ;
			i--;
		}
		if ((error = (character[i].value) ?
					character[i].handler(param, ret) :
					param_addchar(param->buff[param->i], ret)) != ERR_NONE)
			break ;
		param->i++;
	}
	return (error);
}

int				expand_parameter(t_ret *ret, t_exp *param, int (*end)(t_exp *))
{
	int			error;

	if ((error = expand_loop(ret, param, end)) != ERR_NONE)
		return (error);
// 	fieldsplit(&ret);
// 	expand_pathname();
// 	remove_quote(&ret);
	return (ERR_NONE);
}
