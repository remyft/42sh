/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_opt_i.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:21:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/28 20:26:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtin_env.h"

int			builtin_env_opt_i(size_t *i, size_t *j, char **cmd, t_e_opt *opt)
{
	(void)i;
	(void)j;
	(void)cmd;
	opt->i = 1;
	return (ERR_OK);
}
