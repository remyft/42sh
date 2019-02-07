/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:53:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/07 01:15:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"
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
			return (env_error(ERR_MALLOC, 0, &opt));
		if ((error = env_options(&i, &j, exec->cmd, &opt)) != ERR_OK)
			return (env_error(error, &exec->cmd[i][j], &opt));
		if (!exec->cmd[i])
			sh_puttab((const char **)opt.public_env);
		else if ((error = env_exec(exec, i, &opt, e)) != ERR_OK)
			return (env_error(error, &exec->cmd[i][j], &opt));
		env_free_opt(&opt);
	}
	else
		sh_puttab((const char **)e->public_env);
	return (0);
}
