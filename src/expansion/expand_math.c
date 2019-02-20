/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 12:34:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/20 10:52:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_errors.h"

int				expand_math(t_exp *param, t_ret *ret)
{
	(void)param;
	(void)ret;
	param_addchar(param->buff[param->i], ret);
	return (ERR_UNHANDLED);
	return (ERR_NONE);
}
