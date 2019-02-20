/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:24:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/20 10:55:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_errors.h"

int				expand_subshell(t_exp *param, t_ret *ret)
{
	(void)param;
	(void)ret;
	param_addstr("(...)", ret);
	return (ERR_UNHANDLED);
	return (ERR_NONE);
}
