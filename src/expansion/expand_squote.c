/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_squote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 00:17:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/26 10:15:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int				expand_squote(t_exp *param, t_ret *ret)
{
	if (ret->quoted == param->buff[param->i])
		ret->quoted = 0;
	else if (ret->quoted == 0)
		ret->quoted = param->buff[param->i];
	return (param_addchar(param->buff[param->i], ret));
}
