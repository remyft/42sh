/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_opt_u.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:34:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/06 18:50:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "shell_lib.h"
#include "builtin_env.h"

int			env_opt_u(size_t *i, size_t *j, char **cmd, t_e_opt *opt)
{
	char	*var;

	if (!cmd[*i][*j + 1] && !cmd[*i + 1])
		return (ERR_NEED_ARG);
	opt->options |= BUILTIN_OPT_U;
	var = (cmd[*i][*j + 1]) ? &cmd[*i][*j + 1] : cmd[++(*i)];
	if (opt->options & BUILTIN_OPT_V)
	{
		if (ft_printf("#%s unset:\t%s\n", opt->cmdname, var) < 0)
			return (ERR_WRITE);
	}
	sh_unsetenv(var, opt->env);
	return (ERR_OK);
}
