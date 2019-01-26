/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:01:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/26 06:48:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_env.h"
#include "expansion_lib.h"

static char		*cd_recreate_path(char *new, char **list)
{
	int			i;
	char		*tmp;

	i = 0;
	while (list[i])
	{
		tmp = ft_strrchr(new, '/') + 1;
		if (!ft_strcmp(list[i], ".."))
			*tmp = '\0';
		else if (ft_strcmp(list[i], "."))
		{
			if (new[ft_strlen(new) - 1] != '/')
				new = ft_strcat(new, "/");
			new = ft_strcat(new, list[i]);
		}
		i++;
	}
	if (new[1] && new[ft_strlen(new) - 1] == '/')
		new[ft_strlen(new) - 1] = '\0';
	return (new);
}

static char		*cd_get_path(char *path, char *pwd)
{
	char		*new;
	char		**list;

	if (!path)
		return (NULL);
	if (!pwd || !*pwd)
		return (path);
	new = ft_strnew(ft_strlen(path) + ft_strlen(pwd) + 2);
	new = ft_strcpy(new, path);
	list = ft_strsplit(pwd, '/');
	if (new && list)
		new = cd_recreate_path(new, list);
	else
		ft_putendl_fd("cd: memory insufficiant.", STDERR_FILENO);
	if (list)
		ft_freetab(&list);
	return (new);
}

static char		*cd_get_new_pwd(char **args, t_s_env *e, int i)
{
	char		*pwd;

	if (!args[i])
	{
		if (!(pwd = exp_getnenv("HOME", e->public_env)))
			if (!(pwd = exp_getnenv("HOME", e->private_env)))
				ft_putendl_fd("cd: HOME not defined", STDERR_FILENO);
	}
	else if (!ft_strcmp(args[i], "-"))
	{
		if (!(pwd = exp_getnenv("OLDPWD", e->public_env))
			&& !(pwd = exp_getnenv("OLDPWD", e->private_env)))
				ft_putendl_fd("cd: OLDPWD not defined", STDERR_FILENO);
		else if (chdir(pwd) != -1)
			ft_putendl(pwd);
	}
	else if (*args[i] == '/')
		return (cd_get_path("/", args[i]));
	else if ((pwd = exp_getnenv("PWD", e->public_env))
			|| (pwd = exp_getnenv("PWD", e->private_env)))
		return (cd_get_path(pwd, args[i]));
	return (ft_strdup(pwd));
}

int				cd_write_in_pwd(char **args, t_s_env *e, int i)
{
	char		*old_pwd;
	char		*new_pwd;
	int			ret;

	old_pwd = getcwd(NULL, 0);
	new_pwd = cd_get_new_pwd(args, e, i);
	if (chdir(new_pwd) < 0)
		return (cd_dir_error(new_pwd, old_pwd, args[i]));
	if (args[i - 1][0] == '-' &&
		ft_strlen(ft_strrchr(args[i - 1], 'P')) == 1)
	{
		if (new_pwd)
			free(new_pwd);
		new_pwd = getcwd(NULL, 0);
	}
	ret = cd_change_pwds(new_pwd, old_pwd, e);
	if (old_pwd)
		free(old_pwd);
	return (ret);
}
