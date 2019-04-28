/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_change_env.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 18:08:03 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/28 19:15:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_export.h"
#include "shell_lib.h"

void	delete_local(char *arg, t_s_env *e, int i, int j)
{
	char	**save;
	char	*name;
	char	*value;

	if (!(save = e->private_env))
		return ;
	e->private_env = ft_memalloc(sizeof(char **) * (count_strarr(save)));
	name = ft_strsub(arg, 0, var_name_len(arg));
	while (save[i])
	{
		value = ft_strsub(save[i], 0,
				var_name_len(save[i]));
		(ft_strcmp(name, value) == 0) ? i++ : i;
		if (!(save[i]))
		{
			free(value);
			break ;
		}
		e->private_env[j++] = ft_strdup(save[i++]);
		free(value);
	}
	free(name);
	e->private_env[j] = NULL;
	free(save);
	// sh_freetab(&save);
	// save = clone_arr(e->private_env);
	// sh_freetab(&e->private_env);
}

void	delete_exported(char *arg, t_s_env *e, int i, int j)
{
	char	**save;
	char	*name;
	char	*value;

	if (!(save = e->exported_env))
		return ;
	e->exported_env = ft_memalloc(sizeof(char **) * (count_strarr(save)));
	name = ft_strsub(arg, 0, var_name_len(arg));
	while (save[i])
	{
		value = ft_strsub(save[i], 0, var_name_len(save[i]));
		(ft_strcmp(name, value) == 0) ? i++ : i;
		if (!(save[i]))
		{
			free(value);
			break ;
		}
		e->exported_env[j++] = save[i++];
		free(value);
	}
	free(name);
	e->exported_env[j] = NULL;
	free(save);
	// sh_freetab(&save);
	// save = clone_arr(clone);
	// sh_freetab(&clone);
}

void	add_public(char *arg, t_s_env *e)
{
	char	**save;
	char	*tmp;
	int		i;

	i = 0;
	save = e->public_env;
	e->public_env = ft_memalloc(sizeof(char **) * (count_strarr(save) + 2));
	if (save)
		while (save[i])
		{
			e->public_env[i] = save[i];
			i++;
		}
	tmp = (!has_value(arg)) ? ft_strjoin(arg, "=") : ft_strdup(arg);
	e->public_env[i++] = (sh_getnenv(arg, e->private_env)) ? ft_strjoin(tmp,
				sh_getnenv(arg, e->private_env)) : ft_strdup(tmp);
	free(tmp);
	e->public_env[i] = NULL;
	if (save)
		free(save);
	// e->public_env = clone_arr(clone);
	// sh_freetab(&clone);
}

void	add_exported(char *arg, t_s_env *e)
{
	char	**save;
	int		i;

	i = 0;
	save = e->exported_env;
	e->exported_env = ft_memalloc(sizeof(char **) * (count_strarr(save) + 2));
	if (save)
		while (save[i])
		{
			e->exported_env[i] = save[i];
			i++;
		}
	e->exported_env[i++] = ft_strdup(arg);
	e->exported_env[i] = NULL;
	if (save)
		free(save);
}

void	change_public(char *arg, t_s_env *e)
{
	int		i;
	int		len;
	char	*tmp1;
	char	*tmp2;

	i = -1;
	len = var_name_len(arg);
	while (e->public_env[++i])
	{
		tmp1 = ft_strsub(arg, 0, len);
		tmp2 = ft_strsub(e->public_env[i], 0, len);
		if (ft_strcmp(tmp1, tmp2) == 0)
		{
			free(e->public_env[i]);
			e->public_env[i] = ft_strdup(arg);
			if (ft_strncmp("PATH", arg, 4) == 0 && arg[4] == '=')
				check_path(e);
			free(tmp1);
			free(tmp2);
			return ;
		}
		free(tmp1);
		free(tmp2);
	}
}
