/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_opt_i.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:21:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/02 20:28:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtin_env.h"

int			env_opt_i(size_t *i, size_t *j, char **cmd, t_e_opt *opt)
{
	(void)i;
	(void)j;
	(void)cmd;
	opt->options |= BUILTIN_OPT_I;
	return (ERR_OK);
}
