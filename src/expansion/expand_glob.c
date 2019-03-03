/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 03:52:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/03 18:06:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_errors.h"
	#include <stdio.h>
int				expand_glob(t_exp *param, t_ret *ret)
{
	(void)param;
	(void)ret;
	printf("glob: [%.*s]\n", (int)param->buff_len, param->buff + param->i);
	param_addchar(param->buff[param->i], ret);
	return (ERR_UNHANDLED);
	return (ERR_NONE);
}
