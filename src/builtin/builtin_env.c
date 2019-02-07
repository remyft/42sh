/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:53:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/08 00:14:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "builtin_env.h"

int				builtin_env(t_execute *exec, t_s_env *e)
{
	t_e_opt		opt;
	size_t		i;
	size_t		j;
	int			error;

	ft_memset(&opt, 0, sizeof(opt));
	if (exec->cmd[1])
	{
		opt.cmdname = exec->cmd[0];
		if (!(opt.public_env = sh_tabdup((const char **)e->public_env)))
			return (env_error(ERR_MALLOC, 0, &opt, e));
		if ((error = env_options(&i, &j, exec->cmd, &opt)) != ERR_OK)
			return (env_error(error, NULL, &opt, e));
		if (!exec->cmd[i])
		{
			if (sh_puttab((const char **)opt.public_env) < 0)
				return (env_error(ERR_WRITE, &exec->cmd[i][j], &opt, e));
		}
		else if ((error = env_exec(exec, i, &opt, e)) != ERR_OK)
			return (env_error(error, &exec->cmd[i][j], &opt, e));
		env_free_opt(&opt);
	}
	else if (sh_puttab((const char **)e->public_env) < 0)
		return (env_error(ERR_WRITE, NULL, &opt, e));
	return (ERR_OK);
}
