/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 07:44:52 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/08 11:40:52 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	get_cd_error(char *path, char *file)
{
	int error;
	struct stat stat;

	error = access(path, F_OK);
	if (error == -1)
	{
		free(path);
		return (ft_putend(file, " : No such file or directory.\n"));
	}
	if (lstat(path, &stat) == -1)
	{
		free(path);
		return ;
	}
	if (!S_ISDIR(stat.st_mode))
	{
		free(path);
		return (ft_putend(file, " : Not a directory.\n"));
	}
	error = access(path, R_OK);
	if (error == -1)
	{
		free(path);
		return (ft_putend(file, " : Permission denied.\n"));
	}
}

static void	change_dir(char ***env, char *cmd, char *buff, int is_path)
{
	char *path;
	char *pwd;

	if (!is_path && cmd[0] != '/')
	{
		path = ft_strjoin(buff, "/");
		if (chdir(path = ft_strjoinfree(path, cmd, 1)) == -1)
			return (get_cd_error(path, cmd));
	}
	else
	{
		path = ft_strdup(cmd);
		if (chdir(path) == -1)
			return (get_cd_error(path, path));
	}
	pwd = ft_strjoin("PWD=", path);
	ft_setenv(env, pwd, 2);
	free(pwd);
	pwd = ft_strjoin("OLDPWD=", buff);
	ft_setenv(env, pwd, 2);
	free(pwd);
	free(path);
}

void		ft_cd(char ***env, char **cmd)
{
	char	buff[4097];
	char	*str;

	getcwd(buff, 4097);
	if (!cmd[1] || ft_strcmp(cmd[1], "--") == 0 || ft_strcmp(cmd[1], "-") == 0)
	{
		str = get_env(*env, (!cmd[1] || ft_strcmp(cmd[1], "--") == 0
					? "HOME" : "OLDPWD"));
		if (cmd[1] && ft_strcmp(cmd[1], "-") == 0)
			ft_putendl(str);
		change_dir(env, str, buff, 1);
		free(str);
	}
	else if (!cmd[2])
		change_dir(env, cmd[1], buff, 0);
	else if (!cmd[3])
	{
		if (!(str = replace_str(buff, cmd[1], cmd[2])))
			return (ft_putend(cmd[1], " : not in the pwd.\n"));
		change_dir(env, str, buff, 1);
		free(str);
	}
}
