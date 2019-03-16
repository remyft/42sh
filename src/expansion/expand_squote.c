/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_squote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 00:17:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/09 19:59:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_errors.h"

int				expand_squote(t_exp *param, t_ret *ret)
{
	int			error;
	size_t		i;

	error = ERR_NONE;
	i = param->i;
	if (quote_type(param->quote) != DOUBLE_QUOTE)
		while (param->i - i < param->buff_len
		&& (error = param_addchar(param->buff[param->i++], ret)) == ERR_NONE)
			if (param->buff[param->i] == '\'')
				break ;
	return ((error == ERR_NONE && param->i - i < param->buff_len) ?
		param_addchar(param->buff[param->i], ret) : error);
}
