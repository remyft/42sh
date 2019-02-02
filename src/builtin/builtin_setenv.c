/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 09:37:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/01 23:01:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "builtin_setenv.h"

static int		setenv_error(int err, char *cmd_name)
{
	static char	*errors[] = {
		NULL, MALLOC_ERROR, MISSING_ARG, TOO_MANY_ARGS, WRONG_VAR_NAME,
		ALPHA_VAR_NAME,
	};

	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(errors[err], STDERR_FILENO);
	return (1);
}

int				builtin_setenv(t_execute *exec, t_s_env *e)
{
	char		**ptr;

	if (!exec->cmd[1])
		return (sh_puttab((const char **)e->public_env));
	if (!exec->cmd[2])
		return (setenv_error(ERR_MISSING_ARG, exec->cmd[0]));
	if (exec->cmd[3])
		return (setenv_error(ERR_TOO_MANY_ARGS, exec->cmd[0]));
	if (!ft_isalpha(*exec->cmd[1]))
		return (setenv_error(ERR_WRONG_VAR_NAME, exec->cmd[0]));
	if (!sh_stralnum(exec->cmd[1]))
		return (setenv_error(ERR_ALPHA_VAR_NAME, exec->cmd[0]));
	if ((ptr = sh_getnenvaddr(exec->cmd[1], e->private_env)))
		sh_unsetenv(exec->cmd[1], e->private_env);
	if (sh_setenv(exec->cmd[1], exec->cmd[2], &e->public_env))
		return (setenv_error(ERR_MALLOC_ERROR, exec->cmd[0]));
	exec->env = e->public_env;
	return (0);
}
