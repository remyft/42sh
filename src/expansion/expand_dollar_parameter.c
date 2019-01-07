/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_parameter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 04:44:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/07 01:44:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_is.h"
#include "expansion_dollar.h"
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

static int		dollar_parameter_end_digit(t_exp *param)
{
	return (ft_isdigit(param->buff[param->i]));
}

static int		dollar_parameter_end_name(t_exp *param)
{
	return (is_valid_name(param->buff[param->i]));
}

static int		expand_dollar_parameter_init(t_ret *parameter, t_exp *param)
{
	int			(*end)(t_exp *);
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
	end = ft_isdigit(param->buff[param->i]) ? dollar_parameter_end_digit :
											dollar_parameter_end_name;
	if ((error = expand_loop(parameter, param, end)))
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
	if (parameter.brace || !is_expand_null(&parameter) || parameter.hash)
	{
		if ((error = expand_dollar_parameter_value(&parameter, param)))
			return (error);
		if ((error = expand_dollar_get_action(&parameter, param)) != ERR_NONE)
			return (error);
		if (parameter.brace)
			error = expand_dollar_word_value(&parameter, param);
		if (expand_final(parameter.substitute, parameter.hash, ret))
			return (ERR_MALLOC);
	}
	else
		error = expand_final(parameter.word, parameter.hash, ret);
	ret->substitute = parameter.word;
	--param->i;
	return (error);
}
