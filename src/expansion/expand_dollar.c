/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 00:56:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/26 11:03:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

int				expand_dollar(t_exp *param, t_ret *ret)
{
	int			i;

	i = param->i + 1;
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
			{
				// expand_arithmetic();
				return (ERR_NONE);
			}
			// expand_subshell();
		}
	}
	else if (param->buff[i] == '[')
	{
		// expand_arithmetic();
	}
	else
	{
		param->i = i;
		expand_dollar_parameter(param, ret);
	}
	return (ERR_NONE);
}
