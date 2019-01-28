/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:53:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/28 20:51:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "shell_lib.h"
#include "builtin_env.h"
#include "builtins.h"

static int		env_execute(char **cmd, t_e_opt *opt, t_s_env *e)
{
	if (opt->v > 1)
	{
		ft_printf("#env Searching: '%s'\n", opt->path);
		ft_printf("#env  for file: '%s'\n", cmd[0]);
	}
	opt->path = ft_strjoinfree(ft_strjoinfree(opt->path, "/", 1), *cmd, 1);
	if (!opt->path)
		return (ERR_MALLOC);
	opt->freeable = 1;
	if (access(opt->path, F_OK | X_OK))
	{
		ft_dprintf(STDERR_FILENO, "#env: %s: No such file or directory\n",
				cmd[0]);
		e->ret = 127;
		return (ERR_OK);
	}
	else if (opt->v > 1)
		ft_printf("#env   matched: '%s'\n", opt->path);
	if (opt->v)
		ft_printf("#env executing: %s\n", opt->path);
	size_t	j;

	j = 0;
	while (cmd[++j])
	{
		if (opt->v)
			ft_printf("#env    arg[%d]= '%s'", j - 1, cmd[j]);
	return ()
}

static int		env_prepare(t_execute *exec, size_t i, t_e_opt *opt, t_s_env *e)
{
	t_execute	newexec;
	t_s_env		newe;
	int			error;

	ft_memcpy(&newexec, exec, sizeof(newexec));
	newexec.redirection = NULLREDIR;
	newexec.cmd = exec->cmd + i;
	newexec.env = opt->env;
	newexec.builtin = 0;
	ft_memcpy(&newe, e, sizeof(newe));
	newe.progname = "env";
	if (opt->i)
	{
		if (opt->v)
			ft_putendl("#env clearing environ");
		sh_freetab(&opt->env);
	}
	if (opt->path)
		if ((error = env_execute(newexec.cmd, opt, e)) != ERR_OK)
			return (error);
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
		i = 0;
		j = 0;
		if (!(opt.env = ft_tabdup((const char **)e->public_env)))
			return (builtin_env_error(ERR_MALLOC, 0, &opt));
		if ((error = builtin_env_options(&i, &j, exec->cmd, &opt)) != ERR_OK)
			return (builtin_env_error(error, exec->cmd[i][j], &opt));
		if (exec->cmd[i])
			env_prepare(exec->cmd[i], &opt);
		else
			ft_puttab(opt.env);
		builtin_env_free_opt(&opt);
	}
	else
		ft_puttab(e->public_env);
	return (0);
}
