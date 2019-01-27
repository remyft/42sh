/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:26:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 14:16:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "builtins.h"

int				builtin_unsetenv(t_execute *exec, t_s_env *e)
{
	char		**var;
	size_t		i;
	size_t		j;

	i = 1;
	if (!exec->cmd[i])
	{
		ft_putstr_fd(exec->cmd[0], STDERR_FILENO);
		ft_putendl_fd(": missing argument", STDERR_FILENO);
		return (1);
	}
	while (exec->cmd[i])
	{
		if ((var = sh_getnenvaddr(exec->cmd[i], e->public_env)))
		{
			free(*var);
			j = 0;
			while (var[j + 1])
			{
				var[j] = var[j + 1];
				j++;
			}
			var[j] = NULL;
		}
		i++;
	}
	return (0);
}
