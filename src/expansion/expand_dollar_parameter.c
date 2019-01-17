/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_parameter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 04:44:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/16 18:52:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_is.h"
#include "expansion_dollar.h"
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

static int		expand_dollar_parameter_error(int error, t_ret *parameter)
{
	expand_free_t_ret(parameter, 0);
	return (error);
}

int				expand_dollar_parameter(t_exp *param, t_ret *ret)
{
	t_ret		parameter;
	int			error;

	if ((error = expand_dollar_parameter_init(&parameter, param)) != ERR_NONE)
		return (expand_dollar_parameter_error(error, &parameter));
	if (parameter.brace || !is_expand_null(&parameter) || parameter.hash)
	{
		if ((error = expand_dollar_parameter_value(&parameter, param)))
			return (expand_dollar_parameter_error(error, &parameter));
		if ((error = expand_dollar_get_action(&parameter, param)) != ERR_NONE)
			return (expand_dollar_parameter_error(error, &parameter));
		if (parameter.brace)
			error = expand_dollar_word_value(&parameter, param);
		if (expand_final(parameter.substitute, parameter.hash, ret))
			return (expand_dollar_parameter_error(error, &parameter));
	}
	else
		error = expand_final(parameter.word, parameter.hash, ret);
	if (parameter.substitute && parameter.freeable)
		free(parameter.substitute);
	ret->freeable = 1;
	ret->substitute = parameter.word;
	--param->i;
	return (error);
}
