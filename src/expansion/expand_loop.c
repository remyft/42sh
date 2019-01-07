/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 12:00:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/07 01:50:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_loop.h"
#include "expansion_errors.h"
#include "expansion_lib.h"

static int	expand_rules(t_e_character *charact, t_exp *param, t_ret **ret)
{
	int		error;
	char	*ifs;

	if ((error = charact->handler(param, *ret)) != ERR_NONE)
		return (error);
	if (param->quoted || !(*ret)->word || !*(*ret)->word)
		return (error);
	if ((ifs = exp_getnenv("IFS", param->e->private_env)) != NULL)
		error = expand_fieldsplit(ret, ifs);
	return (error);
}

int			expand_loop(t_ret *ret, t_exp *param, int (*end_loop)(t_exp *))
{
	static t_e_character	character[] = {
		OP_EXP_NULL, OP_EXP_BACKSLSH, OP_EXP_SQUOTE, OP_EXP_DQUOTE,
		OP_EXP_TILDE, OP_EXP_DOLLAR, OP_EXP_BACKTICK, OP_EXP_STAR,
		OP_EXP_BRACKET, OP_EXP_QUESTION,
	};
	size_t					i;
	int						error;

	error = ERR_NONE;
	while (error == ERR_NONE && param->i < param->buff_len && end_loop(param))
	{
		i = (param->expand) ? sizeof(character) / sizeof(character[0]) - 1 : 3;
		while (i > 0)
		{
			if (param->buff[param->i] == character[i].value)
				break ;
			i--;
		}
		if (i && param->quoted != '\'')
			error = expand_rules(character + i, param, &ret);
		else
			error = param_addchar(param->buff[param->i], ret);
		param->i++;
	}
	return (error);
}
