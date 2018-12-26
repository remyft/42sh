/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 02:08:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/26 10:14:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int				expand_dquote(t_exp *param, t_ret *ret)
{
	if (ret->quoted == param->buff[param->i])
		ret->quoted = 0;
	else if (ret->quoted == 0)
		ret->quoted = param->buff[param->i];
	return (param_addchar(param->buff[param->i], ret));
}
