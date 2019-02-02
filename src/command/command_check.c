/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:02:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/31 23:24:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "command_error.h"
#include "builtins.h"
#include "libft.h"

int				command_check(t_execute *exec, t_s_env *e)
{
	static t_builtins	builtins[] = {
		BUILTIN_ECHO, BUILTIN_CD, BUILTIN_SETENV, BUILTIN_UNSETENV, BUILTIN_ENV,
		BUILTIN_EXIT,
	};
	size_t				i;

	i = 0;
	while (i < sizeof(builtins) / sizeof(builtins[0]))
	{
		if (!ft_strcmp(builtins[i].name, exec->cmd[0]))
			return (command_builtin(builtins[i].handler, exec, e));
		i++;
	}
	return (command_fork(exec, e));
}
