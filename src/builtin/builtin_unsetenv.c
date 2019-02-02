/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:26:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/01 23:02:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "builtins.h"

int				builtin_unsetenv(t_execute *exec, t_s_env *e)
{
	size_t		i;

	i = 1;
	if (!exec->cmd[i])
	{
		ft_putstr_fd(exec->cmd[0], STDERR_FILENO);
		ft_putendl_fd(": missing argument", STDERR_FILENO);
		return (1);
	}
	while (exec->cmd[i])
	{
		sh_unsetenv(exec->cmd[i], e->public_env);
		sh_unsetenv(exec->cmd[i], e->private_env);
		i++;
	}
	return (0);
}
