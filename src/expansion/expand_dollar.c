/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 00:56:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/27 02:39:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

int				expand_dollar(t_exp *param, t_ret *ret)
{
	int			i;
	int			error;

	i = param->i + 1;
	error = ERR_NONE;
	if (param->buff[i] == '(')
	{
		if (param->buff[i + 1] == '(')
		{
			/* Artihmetic expansion ??? */
			size_t	j = i + 2;
			size_t	depth = 0;

			while (j < param->buff_len
				&& !(depth == 0 && param->buff[j + 1] == ')'))
			{
				if (param->buff[j] == '(')
					++depth;
				else if (param->buff[j] == ')')
					--depth;
				++j;
			}
			if (param->buff[j] == ')' && param->buff[j + 1] == ')')
				;// error = expand_arithmetic();
			else
				;// error = expand_subshell();
		}
	}
	else if (param->buff[i] == '[')
	{
		// expand_arithmetic();
	}
	else
	{
		error = expand_dollar_parameter(param, ret);
	}
	return (error);
}
