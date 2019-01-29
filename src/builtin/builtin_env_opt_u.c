/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_opt_u.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:34:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/29 13:30:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "shell_lib.h"
#include "builtin_env.h"

int			builtin_env_opt_u(size_t *i, size_t *j, char **cmd, t_e_opt *opt)
{
	char	*var;
	char	**addr;
	size_t	nb;

	if (!cmd[*i][*j + 1] && !cmd[*i + 1])
		return (ERR_NEED_ARG);
	var = (cmd[*i][*j + 1]) ? &cmd[*i][*j + 1] : cmd[++(*i)];
	if (opt->v)
	{
		if (ft_dprintf(STDOUT_FILENO, "#env unset:\t%s\n", var) < 0)
			return (ERR_WRITE);
		if ((addr = sh_getnenvaddr(var, opt->env)))
		{
			free(*addr);
			nb = 0;
			while (addr[nb + 1])
			{
				addr[nb] = addr[nb + 1];
				nb++;
			}
			addr[nb] = NULL;
		}
	}
	return (ERR_OK);
}
