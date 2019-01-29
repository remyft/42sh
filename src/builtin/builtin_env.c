/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:53:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/29 14:50:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"
#include "shell_lib.h"
#include "builtin_env.h"
#include "builtins.h"

static int		env_prepare_p(char **cmd, t_e_opt *opt, t_s_env *e)
{
	if (opt->v > 1)
	{
		ft_printf("#%s Searching: '%s'\n", opt->cmdname, opt->path);
		ft_printf("#%s  for file: '%s'\n", opt->cmdname, cmd[0]);
	}
	opt->path = ft_strjoinfree(ft_strjoinfree(opt->path, "/", 1), *cmd, 1);
	if (!opt->path)
		return (ERR_MALLOC);
	opt->freeable = 1;
	if (access(opt->path, F_OK | X_OK))
	{
		// ft_dprintf(STDERR_FILENO, "#env: %s: No such file or directory\n",
		// 		cmd[0]);
		e->ret = 127;
		return (ERR_NOT_FOUND);
	}
	else if (opt->v > 1)
		ft_printf("#%s   matched: '%s'\n", opt->cmdname, opt->path);
	if (opt->v)
		ft_printf("#%s executing: %s\n", opt->cmdname, opt->path);
	return (ERR_OK);
}

static int		env_get_command(char **cmd, t_e_opt *opt)
{
	size_t	i;

	i = 1;
	opt->cmd = (opt->path) ? opt->path : ft_strdup(cmd[0]);
	opt->path = NULL;
	while (cmd[i])
	{
		if (opt->v)
			ft_printf("#%s    arg[%d]= '%s'\n", opt->cmdname, i, cmd[i]);
		opt->cmd = ft_strjoinfree(ft_strjoinfree(opt->cmd, " ", 1), cmd[i], 1);
		if (!opt->cmd)
			return (ERR_MALLOC);
		i++;
	}
	return (ERR_OK);
}

static int		env_prepare(t_execute *exec, size_t i, t_e_opt *opt, t_s_env *e)
{
	t_execute	newexec;
	t_s_env		newe;
	int			error;

	ft_memcpy(&newexec, exec, sizeof(newexec));
	newexec.redirection = NULLREDIR;
	newexec.cmd = exec->cmd + i;
	newexec.builtin = 0;
	ft_memcpy(&newe, e, sizeof(newe));
	newe.progname = opt->cmdname;
	if (opt->i)
	{
		if (opt->v)
			ft_printf("#%s clearing environ\n", opt->cmdname);
		sh_freetab(&opt->env);
	}
	newexec.env = opt->env;
	if (opt->path && exec->cmd[i])
		if ((error = env_prepare_p(exec->cmd + i, opt, e)) != ERR_OK)
			return (error);
	if (exec->cmd[i])
		if (env_get_command(exec->cmd + i, opt) != ERR_OK)
			return (ERR_MALLOC);
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
			return (builtin_env_error(error, exec->cmd[i][j], &opt));
		if ((error = env_prepare(exec, i, &opt, e)) != ERR_OK)
			return (builtin_env_error(error, exec->cmd[i][j], &opt));
		if (!exec->cmd[i])
			sh_puttab((const char **)opt.env);
		builtin_env_free_opt(&opt);
	}
	else
		sh_puttab((const char **)e->public_env);
	return (0);
}
