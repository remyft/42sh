/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:02:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/18 10:18:27 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "builtins.h"
#include "job_control.h"
#include <stdio.h>

int				command_builtin_forked(t_jobs *job, t_process *p, t_s_env *e)
{
	static t_builtins	builtins[] = {
		BUILTIN_ALIAS, BUILTIN_CD, BUILTIN_ECHO, BUILTIN_ENV, BUILTIN_EXIT,
		BUILTIN_SETENV, BUILTIN_UNALIAS, BUILTIN_UNSETENV, BUILTIN_JOBS,
	};
	size_t				i;
	t_execute			*exec;
	
	i = 0;
	(void)job;
	exec = (t_execute *)p->exec;
	if (exec->cmd && exec->cmd[0])
	{
		while (i < sizeof(builtins) / sizeof(builtins[0]))
		{
			if (!ft_strcmp(builtins[i].name, exec->cmd[0]))
				exit(command_builtin(builtins[i].handler, job, p, e));
			i++;
		}
	}
	return (1);
}

int				command_check(t_jobs *job, t_process *p, t_s_env *e)
{
	static t_builtins	builtins[] = {
		BUILTIN_ALIAS, BUILTIN_CD, BUILTIN_ECHO, BUILTIN_ENV, BUILTIN_EXIT,
		BUILTIN_SETENV, BUILTIN_UNALIAS, BUILTIN_UNSETENV, BUILTIN_JOBS,
	};
	size_t				i;
	int					ret;
	t_execute			*exec;

	i = 0;
	ret = 0;
	exec = (t_execute *)p->exec;
	if (exec->cmd && exec->cmd[0])
	{
		while (i < sizeof(builtins) / sizeof(builtins[0]))
		{
			if (!ft_strcmp(builtins[i].name, exec->cmd[0]) && !p->next)
			{
				if (p->pid == 0 && job->foreground == 0)
					return (command_builtin(builtins[i].handler, job, p, e));
			}
			i++;
		}
		ret = command_system(job, p, e);
	}
	return (ret);
}
