/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_change.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:11:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/26 12:20:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cd.h"
#include "expansion_lib.h"
#include "libft.h"

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

	if ((var = exp_getnenvaddr("PWD", e->public_env)))
	{
		free(*var);
		if (!(*var = ft_strjoin("PWD=", new)))
			return (1);
	}
	else if (cd_change_env("PWD=", new, e))
		return (1);
	if ((var = exp_getnenvaddr("OLDPWD", e->public_env)))
	{
		free(*var);
		if (!(*var = ft_strjoin("OLDPWD=", old)))
			return (1);
	}
	else if (cd_change_env("OLDPWD=", old, e))
		return (1);
	return (0);
}