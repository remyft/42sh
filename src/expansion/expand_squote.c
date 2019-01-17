/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_squote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 00:17:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/27 02:20:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int				expand_squote(t_exp *param, t_ret *ret)
{
	if (param->quoted == param->buff[param->i])
		param->quoted = 0;
	else if (param->quoted == 0)
		param->quoted = param->buff[param->i];
	return (param_addchar(param->buff[param->i], ret));
}
