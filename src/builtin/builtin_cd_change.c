/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_change.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:11:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/26 06:47:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_env.h"
#include "expansion_lib.h"

static int	cd_change_error(char *new)
{
	ft_putstr_fd("cd: unable to change pwd: ", STDERR_FILENO);
	ft_putendl_fd(new, STDERR_FILENO);
	return (1);
}

static size_t	cd_tablen(char **table)
{
	size_t		i;

	i = 0;
	if (table)
		while (table[i])
			i++;
	return (i);
}

static int	cd_change_env(char *envvar, char *value, t_s_env *e)
{
	char	**save;
	size_t	len;

	len = cd_tablen(e->public_env);
	save = e->public_env;
	if (!(e->public_env = ft_memalloc(sizeof(value) * (len + 2))))
	{
		e->public_env = save;
		return (cd_change_error(value));
	}
	len = 0;
	if (save)
		while (save[len++])
			e->public_env[len - 1] = save[len - 1];
	if (!(e->public_env[len] = ft_strjoin(envvar, value)))
	{
		free(e->public_env);
		e->public_env = save;
		return (cd_change_error(value));
	}
	if (save)
		free(save);
	return (0);
}

int			cd_change_pwd(char *new, char *old, t_s_env *e)
{
	char	**var;

	if ((var = exp_getnenvaddr("PWD", e->public_env)))
	{
		free(*var);
		if (!(*var = ft_strjoin("PWD=", new)))
			return (cd_change_error(new));
	}
	else if (cd_change_env("PWD=", new, e))
		return (1);
	if ((var = exp_getnenvaddr("OLDPWD", e->public_env)))
	{
		free(*var);
		if (!(*var = ft_strjoin("OLDPWD=", old)))
			return (cd_change_error(old));
	}
	else if (cd_change_env("OLDPWD=", old, e))
		return (1);
	return (0);
}