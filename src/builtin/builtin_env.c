/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:53:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 20:31:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_env.h"
#include "builtins.h"

static int		env_options_check(int *i, int *j, char **command, t_e_opt *opt)
{
	int			error;

	if ((error = builtin_env_check(i, j, command, opt)) != ERR_OK)
		return (error);
	// if ((i = ft_env_check_opt_plus(command, opt, i)) == -1)
	// 	return (-1);
	if (opt->u && ft_opt_u(opt, -1, -1) == -1)
		return (-1);
	if (opt->i)
		ft_opt_i(opt);
	if (opt->extra)
		ft_opt_extra(opt);
	if (opt->p && ft_opt_p(opt, &command[i]) == -1)
		return (-1);
	return (i);
}

int				builtin_env(t_execute *exec, t_s_env *e)
{
	t_e_opt		opt;
	int			i;
	int			j;
	int			error;

	ft_memset(&opt, 0, sizeof(opt));
	if (exec->cmd[1])
	{
		opt.cmdname = exec->cmd[0];
		i = 0;
		j = 0;
		// if (!(opt.cpy = ft_tabdup((const char **)e->public_env)))
		// 	return (builtin_env_error(ERR_MALLOC, 0, &opt));
		if ((error = env_options_check(&i, &j, exec->cmd, &opt)) != ERR_OK)
			return (builtin_env_error(error, exec->cmd[i][j], &opt));
		if (command[i])
			e->ret = check_and_exec(&command[i], opt.cpy, e);
		else
			ft_puttab(opt.cpy);
		ft_freetab(&opt.cpy);
		ft_freestr(&opt.path);
		ft_freestr(&opt.cmd);
		ft_freetab(&opt.ptr);
		free(opt.extra);
	}
	else
		ft_puttab(e->public_env);
	return (e->ret);
}
