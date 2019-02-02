/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_parameter_init.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 22:07:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/30 20:31:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_is.h"
#include "expansion_dollar.h"
#include "expansion_errors.h"

static int		dollar_parameter_end_digit(t_exp *param)
{
	return (ft_isdigit(param->buff[param->i]));
}

static int		dollar_parameter_end_name(t_exp *param)
{
	return (is_valid_name(param->buff[param->i]));
}

int				expand_dollar_parameter_init(t_ret *parameter, t_exp *param)
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
