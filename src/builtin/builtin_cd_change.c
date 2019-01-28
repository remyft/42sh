/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_change.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:11:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/28 18:00:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "builtin_cd.h"

static int	cd_change_env(char *envvar, char *value, t_s_env *e)
{
	char	**save;
	size_t	len;

	len = sh_tablen((const char **)e->public_env);
	save = e->public_env;
	if (!(e->public_env = ft_memalloc(sizeof(value) * (len + 2))))
	{
		e->public_env = save;
		return (ERR_MALLOC);
	}
	len = 0;
	if (save)
		while (save[len++])
			e->public_env[len - 1] = save[len - 1];
	if (!(e->public_env[len] = ft_strjoin(envvar, value)))
	{
		free(e->public_env);
		e->public_env = save;
		return (ERR_MALLOC);
	}
	if (save)
		free(save);
	return (ERR_NO_ERR);
}

int			cd_change_pwds(char *new, char *old, t_s_env *e)
{
	char	**var;

	if ((var = sh_getnenvaddr("PWD", e->public_env)))
	{
		free(*var);
		if (!(*var = ft_strjoin("PWD=", new)))
			return (ERR_MALLOC);
	}
	else if (cd_change_env("PWD=", new, e))
		return (ERR_MALLOC);
	if ((var = sh_getnenvaddr("OLDPWD", e->public_env)))
	{
		free(*var);
		if (!(*var = ft_strjoin("OLDPWD=", old)))
			return (ERR_MALLOC);
	}
	else if (cd_change_env("OLDPWD=", old, e))
		return (ERR_MALLOC);
	return (ERR_NO_ERR);
}
