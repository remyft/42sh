/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:01:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/28 18:34:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "builtin_cd.h"

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

static int		cd_get_path(char **new, char *path, char *pwd)
{
	char		**list;
	size_t		i;

	if (!path)
		return (ERR_NO_ERR);
	if (!pwd || !*pwd)
		return ((*new = ft_strdup(path)) != NULL);
	if (!(*new = ft_strnew(ft_strlen(path) + ft_strlen(pwd) + 2)))
		return (ERR_MALLOC);
	*new = ft_strcpy(*new, path);
	if (!(list = ft_strsplit(pwd, '/')))
		return (ERR_MALLOC);
	*new = cd_recreate_path(*new, list);
	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
	return (ERR_NO_ERR);
}

static int		cd_get_new_pwd(t_execute *exec, t_s_env *e, int i, char **pwd)
{
	if (!exec->cmd[i])
	{
		if (!(*pwd = sh_getnenv("HOME", exec->env)))
			if (!(*pwd = sh_getnenv("HOME", e->private_env)))
				return (ERR_NO_HOME);
	}
	else if (!ft_strcmp(exec->cmd[i], "-"))
	{
		if (!(*pwd = sh_getnenv("OLDPWD", exec->env))
			&& !(*pwd = sh_getnenv("OLDPWD", e->private_env)))
			return (ERR_NO_OLDPWD);
	}
	else if (*exec->cmd[i] == '/')
		return (cd_get_path(pwd, "/", exec->cmd[i]));
	else if ((*pwd = sh_getnenv("PWD", exec->env))
			|| (*pwd = sh_getnenv("PWD", e->private_env)))
		return (cd_get_path(pwd, *pwd, exec->cmd[i]));
	return ((*pwd = ft_strdup(*pwd)) == NULL);
}

int				cd_write_in_pwd(t_execute *exec, t_s_env *e, size_t i)
{
	char		*old_pwd;
	char		*new_pwd;
	int			ret;

	if ((ret = cd_get_new_pwd(exec, e, i, &new_pwd)) != ERR_NO_ERR)
		return (cd_error((ret) ? ret : ERR_MALLOC, exec->cmd[i]));
	if (chdir(new_pwd) < 0)
		return (cd_dir_error(new_pwd, NULL, exec->cmd[i]));
	if (exec->cmd[i - 1][0] == '-' &&
		exec->cmd[i - 1][ft_strlen(exec->cmd[i - 1]) - 1] == 'P')
	{
		if (new_pwd)
			free(new_pwd);
		if (!(new_pwd = getcwd(NULL, 0)))
			return (ERR_MALLOC);
	}
	if (!(old_pwd = getcwd(NULL, 0)))
		ret = ERR_GETCWD;
	else if (exec->env == e->public_env)
		if ((ret = cd_change_pwds(new_pwd, old_pwd, e)) == ERR_NO_ERR
		&& exec->cmd[i] && !ft_strcmp(exec->cmd[i], "-"))
			ft_putendl(new_pwd);
	sh_freestr(&new_pwd);
	sh_freestr(&old_pwd);
	return ((ret) ? cd_error(ret, exec->cmd[i]) : ERR_NO_ERR);
}
