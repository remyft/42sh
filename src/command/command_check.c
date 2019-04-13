/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:02:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/12 17:13:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "builtins.h"

static int		command_check_builtin(int (*handler)(t_execute *, t_s_env *),
t_execute *exec, t_s_env *e)
{
	int			ret;
	int			len;

	ret = command_builtin(handler, exec, e);
	if ((len = sh_tablen((const char **)exec->cmd)))
		len--;
	sh_setenv("_", exec->cmd[len], &e->public_env);
	return (ret);
}

int				command_check(t_execute *exec, t_s_env *e)
{
	static t_builtins	builtins[] = {
		BUILTIN_ALIAS, BUILTIN_CD, BUILTIN_ECHO, BUILTIN_ENV, BUILTIN_EXIT,
		BUILTIN_SETENV, BUILTIN_SOURCE, BUILTIN_UNALIAS, BUILTIN_UNSETENV,
	};
	size_t				i;
	int					ret;
	int					len;

	i = 0;
	ret = 0;
	if (exec->cmd && exec->cmd[0])
	{
		sh_setenv("_", exec->cmd[0], &e->public_env);
		while (i < sizeof(builtins) / sizeof(builtins[0]))
		{
			if (!ft_strcmp(builtins[i].name, exec->cmd[0]))
				return (command_check_builtin(builtins[i].handler, exec, e));
			i++;
		}
		ret = command_system(exec, e);
		if ((len = sh_tablen((const char **)exec->cmd)))
			len--;
		sh_setenv("_", exec->cmd[len], &e->public_env);
	}
	return (ret);
}
