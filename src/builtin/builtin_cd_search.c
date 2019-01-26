/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:03:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/26 06:49:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_env.h"
#include "builtin_cd.h"

static char		*cd_change_in_pwd(char *pwd, char *spot, char **args)
{
	char		*tmp;

	if ((tmp = ft_strndup(pwd, ft_strlen(pwd) - ft_strlen(spot))))
	{
		pwd = ft_strjoin(tmp, args[2]);
		free(tmp);
		tmp = NULL;
		if (pwd)
		{
			tmp = ft_strjoin(pwd, spot + ft_strlen(args[1]));
			free(pwd);
		}
	}
	return (tmp);
}

int				cd_search_in_pwd(char **args, t_s_env *e)
{
	char		*old_pwd;
	char		*new_pwd;
	char		*tmp;
	int			ret;

	if (!(old_pwd = getcwd(NULL, 0)) || !(tmp = ft_strstr(old_pwd, args[1])))
	{
		if (old_pwd)
			free(old_pwd);
		return (cd_error(ERR_NOT_IN_PWD, args[1]));
	}
	new_pwd = cd_change_in_pwd(old_pwd, tmp, args);
	if (chdir(new_pwd) != -1)
	{
		ft_putendl(new_pwd);
		ret = cd_change_pwds(new_pwd, old_pwd, e);
		if (old_pwd)
			free(old_pwd);
		return (ret);
	}
	return (cd_dir_error(new_pwd, old_pwd, new_pwd));
}
