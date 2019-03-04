/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_opt_i.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:21:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/03 19:13:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtin_env.h"

int			env_opt_i(char **cmd, t_e_opt *opt)
{
	if (cmd[opt->i][opt->j] == '-' && opt->j == 1 && !cmd[opt->i][opt->j + 1])
		opt->options |= BUILTIN_OPT_END;
	else
		opt->options |= BUILTIN_OPT_I;
	return (ERR_OK);
}
