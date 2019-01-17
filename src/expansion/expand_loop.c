/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 12:00:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/14 18:17:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_loop.h"
#include "expansion_errors.h"
#include "expansion_lib.h"

static int		expand_rules(t_e_character *charact, t_exp *param, t_ret **ret)
{
	int		error;
	char	*ifs;

	if (param->quoted == '\'' && param->buff[param->i] != '\'')
		return (param_addchar(param->buff[param->i], *ret));
	if ((error = charact->handler(param, *ret)) != ERR_NONE)
		return (error);
	if (param->quoted || !(*ret)->word || !*(*ret)->word || !param->fieldsplit)
		return (error);
	if ((ifs = exp_getnenv("IFS", param->e->private_env)) != NULL)
		error = expand_fieldsplit(ret, ifs);
	return (error);
}

static size_t	expand_i_value(t_exp *param, size_t size)
{
	if (param->expand)
		return (size);
	if (param->quoted == '\'')
		return (1);
	if (param->quoted == '"')
		return (3);
	return (3);
}

int				expand_loop(t_ret *ret, t_exp *param, int (*end_loop)(t_exp *))
{
	static t_e_character	character[] = {
		OP_EXP_SQUOTE, OP_EXP_BACKSLSH, OP_EXP_DQUOTE,
		OP_EXP_TILDE, OP_EXP_DOLLAR, OP_EXP_BACKTICK, OP_EXP_STAR,
		OP_EXP_BRACKET, OP_EXP_QUESTION,
	};
	size_t					i;
	int						error;

	error = ERR_NONE;
	while (error == ERR_NONE && param->i < param->buff_len && end_loop(param))
	{
		i = expand_i_value(param, sizeof(character) / sizeof(character[0]));
		while (i-- > 0)
			if (param->buff[param->i] == character[i].value)
			{
				error = expand_rules(character + i, param, &ret);
				break ;
			}
		if (!(i + 1))
			error = param_addchar(param->buff[param->i], ret);
		param->i++;
	}
	return (error);
}
