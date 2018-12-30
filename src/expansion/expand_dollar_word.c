/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 10:27:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/28 12:23:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int				expand_dollar_word(t_ret *ret, t_exp *param, char op, char cl)
{
	int			depth;
	char		quote;
	char		c;

	depth = 0;
	quote = 0;
	c = param->buff[param->i];
	while (c != cl || depth || quote)
	{
		if (c == '"')
		{
			if (quote == 0)
				quote = '"';
			else if (quote == '"')
				quote = 0;
		}
		else if (c == '\'')
		{
			if (quote == 0)
				quote = '\'';
			else if (quote == '\'')
				quote = 0;
		}
		else if (c == '\\')
			++param->i;
		else if (c == op && !quote)
			++depth;
		else if (c == cl && !quote)
			--depth;
		if (param_addchar(c, ret))
			return (ERR_MALLOC);
		++param->i;
		c = param->buff[param->i];
	}
	return (ERR_NONE);
}
