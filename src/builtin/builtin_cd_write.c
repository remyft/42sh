/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:01:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/02 19:56:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include "libft.h"
#include "shell_lib.h"
#include "builtin_cd.h"

static int		cd_get_path(char *pwd, char *path)
{
	if (*path == '/')
		ft_strncpy(pwd, path, MAXPATHLEN);
	else if (getcwd(pwd, MAXPATHLEN) == NULL)
		return (ERR_GETCWD);
	else
	{
		ft_strncat(pwd, "/", MAXPATHLEN);
		ft_strncat(pwd, path, MAXPATHLEN);
	}
	pwd = cd_recreate_path(pwd);
	return (ERR_NO_ERR);
}

static int		cd_get_new_pwd(t_execute *exec, t_s_env *e, int i, char *pwd)
{
	char		*path;

	if (!exec->cmd[i])
	{
		if (!(path = sh_getnenv("HOME", exec->env)))
			if (!(path = sh_getnenv("HOME", e->private_env)))
				return (ERR_NO_HOME);
	}
	else if (!ft_strcmp(exec->cmd[i], "-"))
	{
		if (!(path = sh_getnenv("OLDPWD", exec->env))
			&& !(path = sh_getnenv("OLDPWD", e->private_env)))
			return (ERR_NO_OLDPWD);
	}
	else
		return (cd_get_path(pwd, exec->cmd[i]));
	ft_strncpy(pwd, path, MAXPATHLEN);
	return (ERR_NO_ERR);
}

int				cd_write_in_pwd(t_execute *exec, t_s_env *e, size_t i)
{
	char		new_pwd[MAXPATHLEN];
	int			ret;

	if ((ret = cd_get_new_pwd(exec, e, i, new_pwd)) != ERR_NO_ERR)
		return (cd_error(ret, exec->cmd[i]));
	if (chdir(new_pwd) < 0)
		return (cd_dir_error(new_pwd, exec->cmd[i]));
	if (exec->cmd[i - 1][0] == '-' &&
		exec->cmd[i - 1][ft_strlen(exec->cmd[i - 1]) - 1] == 'P')
	{
		if (getcwd(new_pwd, MAXPATHLEN) == NULL)
			return (ERR_GETCWD);
	}
	if (exec->env == e->public_env)
		if ((ret = cd_change_pwds(new_pwd, e)) == ERR_NO_ERR
		&& exec->cmd[i] && !ft_strcmp(exec->cmd[i], "-"))
			ft_putendl(new_pwd);
	return ((ret) ? cd_error(ret, exec->cmd[i]) : ERR_NO_ERR);
}
