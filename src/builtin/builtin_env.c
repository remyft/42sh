/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:53:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/30 20:04:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"
#include "shell_lib.h"
#include "builtin_env.h"
#include "builtins.h"

static int		env_prepare_command(char **cmd, t_e_opt *opt)
{
	if (!opt->path || ft_strchr(cmd[0], '/'))
	{
		opt->cmd = ft_strdup(cmd[0]);
		return (ERR_OK);
	}
	if (opt->verbosity > 1)
	{
		ft_printf("#%s Searching: '%s'\n", opt->cmdname, opt->path);
		ft_printf("#%s  for file: '%s'\n", opt->cmdname, cmd[0]);
	}
	if (!(opt->cmd = ft_strjoinfree(ft_strjoin(opt->path, "/"), cmd[0], 1)))
		return (ERR_MALLOC);
	if (access(opt->cmd, F_OK | X_OK))
		return (ERR_NOT_FOUND);
	else if (opt->verbosity > 1)
		ft_printf("#%s   matched: '%s'\n", opt->cmdname, opt->cmd);
	return (ERR_OK);
}

static int		env_get_command(char **cmd, t_e_opt *opt)
{
	size_t	i;

	i = 1;
	if (opt->options & BUILTIN_OPT_V)
		ft_printf("#%s    arg[%d]= '%s'\n", opt->cmdname, 0, opt->cmd);
	while (cmd[i])
	{
		if (opt->options & BUILTIN_OPT_V)
			ft_printf("#%s    arg[%d]= '%s'\n", opt->cmdname, i, cmd[i]);
		if (!(opt->cmd = ft_strjoinfree(opt->cmd, " ", 1))
		|| !(opt->cmd = ft_strjoinfree(opt->cmd, cmd[i], 1)))
			return (ERR_MALLOC);
		i++;
	}
	return (ERR_OK);
}

static int		env_prepare(t_execute *exec, size_t i, t_e_opt *opt, t_s_env *e)
{
	t_s_env		newe;
	int			error;

	if (opt->options & BUILTIN_OPT_I)
	{
		if (opt->options & BUILTIN_OPT_V)
			ft_printf("#%s clearing environ\n", opt->cmdname);
		sh_freetab(&opt->env);
	}
	if ((error = env_prepare_command(exec->cmd + i, opt)) != ERR_OK)
		return (error);
	if (opt->options & BUILTIN_OPT_V)
		ft_printf("#%s executing: %s\n", opt->cmdname, opt->cmd);
	if (env_get_command(exec->cmd + i, opt) != ERR_OK)
		return (ERR_MALLOC);
	ft_memcpy(&newe, e, sizeof(newe));
	newe.progname = opt->cmdname;
	newe.public_env = opt->env;
	launch_new_cmd(&opt->cmd, e);
	return (ERR_OK);
}

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
		if (!(opt.env = sh_tabdup((const char **)e->public_env)))
			return (builtin_env_error(ERR_MALLOC, 0, &opt));
		if ((error = builtin_env_options(&i, &j, exec->cmd, &opt)) != ERR_OK)
			return (builtin_env_error(error, &exec->cmd[i][j], &opt));
		if (!exec->cmd[i])
			sh_puttab((const char **)opt.env);
		else if ((error = env_prepare(exec, i, &opt, e)) != ERR_OK)
			return (builtin_env_error(error, &exec->cmd[i][j], &opt));
		builtin_env_free_opt(&opt);
	}
	else
		sh_puttab((const char **)e->public_env);
	return (0);
}
