/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_backtick.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 03:51:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/20 10:54:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_errors.h"

int			expand_backtick(t_exp *param, t_ret *ret)
{
	(void)param;
	(void)ret;
	param_addstr("`...`", ret);
	return (ERR_UNHANDLED);
	return (ERR_NONE);
}
