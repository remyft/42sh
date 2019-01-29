/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_opt_v.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 12:31:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/29 13:31:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "builtin_env.h"

int			builtin_env_opt_v(size_t *i, size_t *j, char **cmd, t_e_opt *opt)
{
	(void)i;
	(void)j;
	(void)cmd;
	opt->v += 1;
	if (opt->v > 1)
		if (ft_dprintf(STDOUT_FILENO, "#env verbosity now at %d\n", opt->v) < 0)
			return (ERR_WRITE);
	return (ERR_OK);
}
