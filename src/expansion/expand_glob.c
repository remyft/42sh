/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 03:52:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/08 17:36:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_errors.h"
#include "struct.h"
#include "shell.h"
#include "libft.h"

int				expand_glob(t_exp *param, t_ret *ret)
{
	param_addchar(param->buff[param->i], ret);
	return (ERR_UNHANDLED);
	return (ERR_NONE);
}
