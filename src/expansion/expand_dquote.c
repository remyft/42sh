/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 02:08:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/27 02:20:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int				expand_dquote(t_exp *param, t_ret *ret)
{
	if (param->quoted == param->buff[param->i])
		param->quoted = 0;
	else if (param->quoted == 0)
		param->quoted = param->buff[param->i];
	return (param_addchar(param->buff[param->i], ret));
}
