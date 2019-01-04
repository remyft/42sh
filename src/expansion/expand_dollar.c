/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 00:56:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/03 20:42:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

static int		check_expression(t_exp *param)
{
	size_t	j;
	size_t	depth;

	j = param->i + 2;
	depth = 0;
	while (j < param->buff_len
		&& !(depth == 0 && param->buff[j + 1] == ')'))
	{
		if (param->buff[j] == '(')
			++depth;
		else if (param->buff[j] == ')')
			--depth;
		++j;
	}
	return (param->buff[j] == ')' && param->buff[j + 1] == ')');
}

int				expand_dollar(t_exp *param, t_ret *ret)
{
	int			i;

	i = param->i + 1;
	if (param->buff[i] == '(')
	{
		if (param->buff[i + 1] == '(' && check_expression(param))
			return (expand_arithmetic(param, ret));
		return (expand_subshell(param, ret));
	}
	else if (param->buff[i] == '[')
		return (expand_arithmetic(param, ret));
	return (expand_dollar_parameter(param, ret));
}
