/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 09:37:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 13:44:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "builtin_setenv.h"

// static int			add_entry(int i, char **entry, t_env *e)
// {
// 	char		**new_env;
// 	char		*ptr;

// 	if ((new_env = malloc(sizeof(*new_env) * (ft_tablen(e->env) + 2))))
// 	{
// 		while (e->env[++i])
// 			new_env[i] = e->env[i];
// 		if ((ptr = ft_strchr(entry[1], '=')) != NULL)
// 			*(ptr - 1) = '\0';
// 		new_env[i] = malloc(ft_strlen(entry[1]) + ft_strlen(entry[2]) + 2);
// 		if (new_env[i])
// 		{
// 			ft_strcpy(new_env[i], entry[1]);
// 			ft_strcat(new_env[i], "=");
// 			ft_strcat(new_env[i], entry[2]);
// 			new_env[i + 1] = NULL;
// 			free(e->env);
// 			e->env = new_env;
// 			return (0);
// 		}
// 		free(new_env);
// 	}
// 	ft_putendl_fd("setenv: Memory space insufficiant.", 2);
// 	return (1);
// }

// static int			modify_entry(char **entry, t_env *e)
// {
// 	char		**tmp;
// 	char		*new_entry;
// 	int			len;

// 	tmp = ft_getenvaddr(entry[1], e->env);
// 	len = ft_strlen(entry[1]) + ft_strlen(entry[2]) + 2;
// 	if ((new_entry = malloc(len)) != NULL)
// 	{
// 		ft_strcpy(new_entry, entry[1]);
// 		ft_strcat(new_entry, "=");
// 		ft_strcat(new_entry, entry[2]);
// 		free(*tmp);
// 		*tmp = new_entry;
// 		return (0);
// 	}
// 	ft_putendl_fd("setenv: Memory space insufficiant.", 2);
// 	return (1);
// }

static int		setenv_error(int err, char *cmd_name)
{
	static char	*errors[] = {
		NULL, MALLOC_ERROR, MISSING_ARG, TOO_MANY_ARGS, WRONG_VAR_NAME, ALPHA_VAR_NAME,
	};

	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(errors[err], STDERR_FILENO);
	return (1);
}

static int		setenv_modify(t_execute *exec, t_s_env *e)
{
	char		**pos;
	char		*newvar;

	newvar = ft_strjoinfree(ft_strjoin(exec->cmd[1], "="), exec->cmd[2], 1);
	if (!newvar)
		return (setenv_error(ERR_MALLOC_ERROR, exec->cmd[0]));
	if (!(pos = sh_getnenvaddr(exec->cmd[1], e->public_env)))
		if (!(pos = sh_newenv(&e->public_env)))
			return (setenv_error(ERR_MALLOC_ERROR, exec->cmd[0]));
	if (*pos)
		free(*pos);
	*pos = newvar;
	exec->env = e->public_env;
	return (0);
}

int				builtin_setenv(t_execute *exec, t_s_env *e)
{
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
	return (setenv_modify(exec, e));
}
