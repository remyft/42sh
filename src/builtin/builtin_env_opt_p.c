/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_opt_p.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:33:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/28 20:25:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtin_env.h"

int			builtin_env_opt_p(size_t *i, size_t *j, char **cmd, t_e_opt *opt)
{
	if (cmd[*i][*j + 1] || cmd[*i + 1])
	{
		opt->path = (cmd[*i][*j + 1]) ?
					&cmd[*i][*j + 1] : cmd[++(*i)];
		return (ERR_OK);
	}
	return (ERR_NEED_ARG);
}
