/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:03:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/26 18:29:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execution.h"
#include "shell_env.h"
#include "builtin_cd.h"

static char		*cd_change_in_pwd(char *pwd, char *spot, char **args)
{
	char		*tmp;
	char		*ptr;

	ptr = pwd;
	tmp = ft_strndup(pwd, ft_strlen(pwd) - ft_strlen(spot));
	if (!tmp)
	{
		free(pwd);
		return (NULL);
	}
	pwd = ft_strjoin(tmp, args[2]);
	free(tmp);
	if (!pwd)
	{
		free(ptr);
		return (NULL);
	}
	tmp = ft_strjoin(pwd, spot + ft_strlen(args[1]));
	free(ptr);
	free(pwd);
	return (tmp);
}

int				cd_search_in_pwd(t_execute *exec, t_s_env *e, size_t i)
{
	char		*old_pwd;
	char		*new_pwd;
	int			ret;

	if (!(new_pwd = getcwd(NULL, 0)))
		return (cd_error(ERR_MALLOC, exec->cmd[i]));
	if (!(old_pwd = ft_strstr(new_pwd, exec->cmd[i + 1])))
	{
		free(new_pwd);
		return (cd_error(ERR_NOT_IN_PWD, exec->cmd[i + 1]));
	}
	if (!(new_pwd = cd_change_in_pwd(new_pwd, old_pwd, exec->cmd + i)))
		return (cd_error(ERR_MALLOC, exec->cmd[i]));
	if (chdir(new_pwd) < 0)
		return (cd_dir_error(new_pwd, NULL, new_pwd));
	ft_putendl(new_pwd);
	ret = cd_change_pwds(new_pwd, old_pwd, e);
	if (old_pwd)
		free(old_pwd);
	return ((ret) ? cd_error(ret, exec->cmd[i]) : ERR_NO_ERR);
}
