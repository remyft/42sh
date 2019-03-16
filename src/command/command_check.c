/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:02:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/11 17:57:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "builtins.h"

int				command_check(t_jobs *job, t_process *p, t_s_env *e)
{
	static t_builtins	builtins[] = {
		BUILTIN_ALIAS, BUILTIN_CD, BUILTIN_ECHO, BUILTIN_ENV, BUILTIN_EXIT,
		BUILTIN_SETENV, BUILTIN_UNALIAS, BUILTIN_UNSETENV,
	};
	size_t				i;
	int					ret;
	t_execute			*exec;

	i = 0;
	ret = 0;
	exec = (t_execute *)p->exec;
	if (exec->cmd && exec->cmd[0])
	{
		if ((ret = sh_tablen((const char **)exec->cmd)))
			ret--;
		sh_setenv("_", exec->cmd[ret], &e->public_env);
		while (i < sizeof(builtins) / sizeof(builtins[0]))
		{
			if (!ft_strcmp(builtins[i].name, exec->cmd[0]))
				return (command_builtin(builtins[i].handler, exec, e));
			i++;
		}
		ret = command_system(job, p, e);
	}
	command_free(exec, NULL);
	return (ret);
}

int			command_job(t_jobs *job, t_s_env *e)
{
	int		ret;

	ret = 0;
	for (t_process *p = job->process; p; p = p->next)
		ret = command_check(job, p, e);
	return (0);
}



