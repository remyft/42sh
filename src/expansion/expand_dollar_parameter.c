/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_parameter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 04:44:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/30 17:58:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_parameter.h"
#include "expansion_action.h"

static int		dollar_parameter_end(t_exp *param)
{
	return (is_valid_name(param->buff[param->i]));
}

int				expand_dollar_parameter(t_exp *param, t_ret *ret)
{
	t_ret		parameter;
	int			error;

	ft_memset(&parameter, 0, sizeof(parameter));
	error = ERR_NONE;
	if (param_addchar(param->buff[param->i++], &parameter))
		return (ERR_MALLOC);
	if ((parameter.brace = param->buff[param->i] == '{')
		&& param_addchar(param->buff[param->i++], &parameter))
		return (ERR_MALLOC);
	if ((parameter.hash = param->buff[param->i] == '#')
		&& param_addchar(param->buff[param->i++], &parameter))
		return (ERR_MALLOC);
	if ((error = expand_mword(&parameter, param, dollar_parameter_end)))
		return (error);
	if (is_expand_null(&parameter)
		&& is_special(param->buff[param->i])
		&& param_addchar(param->buff[param->i++], &parameter))
		return (ERR_MALLOC);
	if (parameter.brace || !is_expand_null(&parameter))
	{
		if ((error = expand_dollar_parameter_value(&parameter, param)))
			return (error);
debug_expansion("param", &parameter, param);
		if ((error = expand_dollar_get_action(&parameter, param)))
			return (error);
		if ((error = expand_dollar_word_value(&parameter, param)))
			return (error);
		if (parameter.substitute)
			param_addstr(parameter.substitute, ret);
		// else
		// 	param_addstr(parameter.word, ret);
debug_expansion("param", &parameter, param);
	}
	else
		param_addstr(parameter.word, ret);
	ret->substitute = parameter.word;
debug_expansion("ret", ret, param);
	--param->i;
	return (error);
}
