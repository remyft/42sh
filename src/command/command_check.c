/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:02:57 by gbourgeo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/02/23 16:30:02 by dbaffier         ###   ########.fr       */
=======
/*   Updated: 2019/02/24 18:39:48 by gbourgeo         ###   ########.fr       */
>>>>>>> 0da62b1aea1eb542d11da9bd1755dd461c2b81ca
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"
#include "builtins.h"

int				command_check(t_execute *exec, t_s_env *e)
{
	static t_builtins	builtins[] = {
		BUILTIN_ALIAS, BUILTIN_CD, BUILTIN_ECHO, BUILTIN_ENV, BUILTIN_EXIT,
		BUILTIN_SETENV, BUILTIN_UNALIAS, BUILTIN_UNSETENV,
	};
	size_t				i;

	i = 0;
	if (!exec->cmd || !exec->cmd[0])
		return (0);
	while (i < sizeof(builtins) / sizeof(builtins[0]))
	{
		if (!ft_strcmp(builtins[i].name, exec->cmd[0]))
			return (command_builtin(builtins[i].handler, exec, e));
		i++;
	}
	return (command_system(exec, e));
}
