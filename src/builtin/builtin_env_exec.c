/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 01:15:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/09 03:09:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "shell_lib.h"
#include "builtin_env.h"

static int		env_fork(t_e_opt *opt, t_s_env *e)
{
	t_s_env		newe;
	pid_t		pid;

	ft_memcpy(&newe, e, sizeof(newe));
	newe.progname = opt->cmdname;
	newe.public_env = opt->public_env;
	newe.forked = 1;
	if ((pid = fork()) > 0)
		waitpid(pid, &e->ret, 0);
	else if (pid == 0)
	{
		launch_new_cmd(&opt->cmd, &newe);
		exit(newe.ret);
	}
	else
		return (ERR_FORK);
	return (ERR_OK);
}

static int		env_prepare_command(char **cmd, t_e_opt *opt)
{
	if (!opt->path || ft_strchr(cmd[0], '/'))
	{
		if (!opt->cmd)
		{
			if (!(opt->cmd = ft_strdup(cmd[0])))
				return (ERR_MALLOC);
		}
		else if (!(opt->cmd = ft_strjoinfree(opt->cmd, " ", 1))
			|| !(opt->cmd = ft_strjoinfree(opt->cmd, cmd[0], 1)))
			return (ERR_MALLOC);
		return (ERR_OK);
	}
	if (opt->verbosity > 1
	&& (ft_printf("#%s Searching: '%s'\n", opt->cmdname, opt->path) < 0
		|| ft_printf("#%s  for file: '%s'\n", opt->cmdname, cmd[0]) < 0))
		return (ERR_WRITE);
	if (!(opt->cmd = ft_strjoinfree(ft_strjoin(opt->path, "/"), cmd[0], 1)))
		return (ERR_MALLOC);
	if (access(opt->cmd, F_OK | X_OK))
		return (ERR_NOT_FOUND);
	else if (opt->verbosity > 1
	&& ft_printf("#%s   matched: '%s'\n", opt->cmdname, opt->cmd) < 0)
		return (ERR_WRITE);
	return (ERR_OK);
}

static int		env_get_command(char **cmd, t_e_opt *opt)
{
	size_t		i;

	i = 1;
	if (opt->options & BUILTIN_OPT_V
	&& ft_printf("#%s    arg[%d]= '%s'\n", opt->cmdname, 0, opt->cmd) < 0)
		return (ERR_WRITE);
	while (cmd[i])
	{
		if (opt->options & BUILTIN_OPT_V
		&& ft_printf("#%s    arg[%d]= '%s'\n", opt->cmdname, i, cmd[i]) < 0)
			return (ERR_WRITE);
		if (!(opt->cmd = ft_strjoinfree(opt->cmd, " ", 1))
		|| !(opt->cmd = ft_strjoinfree(opt->cmd, cmd[i], 1)))
			return (ERR_MALLOC);
		i++;
	}
	return (ERR_OK);
}

int				env_exec(t_execute *exec, size_t i, t_e_opt *opt, t_s_env *e)
{
	int			error;

	if (opt->options & BUILTIN_OPT_I)
	{
		if (opt->options & BUILTIN_OPT_V
		&& ft_printf("#%s clearing environ\n", opt->cmdname) < 0)
			return (ERR_WRITE);
		sh_freetab(&opt->public_env);
	}
	if ((error = env_prepare_command(exec->cmd + i, opt)) != ERR_OK)
		return (error);
	if (opt->options & BUILTIN_OPT_V
	&& ft_printf("#%s executing: %s\n", opt->cmdname, opt->cmd) < 0)
		return (ERR_WRITE);
	if ((error = env_get_command(exec->cmd + i, opt)) != ERR_OK)
		return (error);
	return (env_fork(opt, e));
}
