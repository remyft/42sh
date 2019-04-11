/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:53:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/09 16:18:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "shell_lib.h"
#include "builtin_env.h"
#include "builtins.h"

static int		builtin_env_aff(t_e_opt *opt)
{
	if (!(opt->options & BUILTIN_OPT_I)
	&& sh_puttab((const char **)opt->public_env) < 0)
		return (1);
	else if (opt->options & BUILTIN_OPT_V
	&& ft_dprintf(STDERR_FILENO, "#%s clearing environ\n", opt->cmdname) < 0)
		return (1);
	return (0);
}

int				builtin_env(t_execute *exec, t_s_env *e)
{
	t_e_opt		opt;
	int			error;

	ft_memset(&opt, 0, sizeof(opt));
	e->ret = 0;
	if (exec->cmd[1])
	{
		opt.cmdname = exec->cmd[0];
		if (!(opt.public_env = sh_tabdup((const char **)e->public_env)))
			return (env_error(ERR_MALLOC, NULL, &opt, e));
		if ((error = env_options(exec->cmd, &opt)) != ERR_OK)
			return (env_error(error, exec->cmd[opt.i], &opt, e));
		if (!exec->cmd[opt.i])
		{
			if (builtin_env_aff(&opt))
				return (env_error(ERR_WRITE, exec->cmd[opt.i], &opt, e));
		}
		else if ((error = env_exec(exec, &opt, e)) != ERR_OK)
			return (env_error(error, exec->cmd[opt.i], &opt, e));
		env_free_opt(&opt);
	}
	else if (sh_puttab((const char **)e->public_env) < 0)
		return (env_error(ERR_WRITE, NULL, &opt, e));
	return (e->ret);
}
