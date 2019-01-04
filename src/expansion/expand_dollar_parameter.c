/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_parameter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 04:44:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/04 03:00:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_action.h"
#include "expansion_errors.h"

static int		expand_final(char *str, int hash, t_ret *ret)
{
	char		*nb;
	int			error;

	if (!hash)
		return (param_addstr(str, ret));
	if (!(nb = ft_itoa((str) ? ft_strlen(str) : 0)))
		return (ERR_MALLOC);
	error = param_addstr(nb, ret);
	free(nb);
	return (error);
}

static int		dollar_parameter_end(t_exp *param)
{
	return (is_valid_name(param->buff[param->i]));
}

static int		expand_dollar_parameter_init(t_ret *parameter, t_exp *param)
{
	int			error;

	error = ERR_NONE;
	ft_memset(parameter, 0, sizeof(*parameter));
	if (param_addchar(param->buff[param->i++], parameter))
		return (ERR_MALLOC);
	if ((parameter->brace = param->buff[param->i] == '{')
		&& param_addchar(param->buff[param->i++], parameter))
		return (ERR_MALLOC);
	if ((parameter->hash = param->buff[param->i] == '#')
		&& param_addchar(param->buff[param->i++], parameter))
		return (ERR_MALLOC);
	if ((error = expand_parameter(parameter, param, dollar_parameter_end)))
		return (error);
	if (is_expand_null(parameter)
		&& is_special(param->buff[param->i])
		&& param_addchar(param->buff[param->i++], parameter))
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int				expand_dollar_parameter(t_exp *param, t_ret *ret)
{
	t_ret		parameter;
	int			error;

	if ((error = expand_dollar_parameter_init(&parameter, param)) != ERR_NONE)
		return (error);
	if (parameter.brace || !is_expand_null(&parameter))
	{
		if ((error = expand_dollar_parameter_value(&parameter, param)))
			return (error);
//		debug_expansion("param", &parameter);
		if ((error = expand_dollar_get_action(&parameter, param)))
			return (error);
		if ((error = expand_dollar_word_value(&parameter, param)))
			return (error);
		error = expand_final(parameter.substitute, parameter.hash, ret);
//		debug_expansion("param", &parameter);
	}
	else
	{
		error = expand_final(parameter.word, parameter.hash, ret);
		--param->i;
	}
	ret->substitute = parameter.word;
//	debug_expansion("ret", ret);
	return (error);
}
