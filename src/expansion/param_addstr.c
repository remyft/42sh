/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_addstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 04:03:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/30 10:57:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int				param_addstr(char *str, t_ret *ret)
{
	if (!str)
		return (ERR_NONE);
	while (*str)
	{
		if (param_addchar(*str, ret) != ERR_NONE)
			return (ERR_MALLOC);
		str++;
	}
	return (ERR_NONE);
}
