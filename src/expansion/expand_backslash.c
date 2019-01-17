/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 23:53:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/05 18:42:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_errors.h"

int			expand_backslash(t_exp *param, t_ret *ret)
{
	int		error;

	error = param_addchar(param->buff[param->i++], ret);
	if (error == ERR_NONE && param->quoted != '\'')
		error = param_addchar(param->buff[param->i], ret);
	return (error);
}
