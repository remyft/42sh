/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 10:20:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/26 06:15:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat>
#include "libft.h"

int				cd_error(int err, char *arg)
{
	static char	*errors[] = {
		"invalid option: -", "too much arguments", "string not in pwd",
	};

	ft_putstr_fd("cd: ", STDERR_FILENO);
	if (err)
	{
		ft_putstr_fd(errors[err], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(arg, STDERR_FILENO);
	}
	else
	{
		ft_putchar_fd(*arg, STDERR_FILENO);
		ft_putendl_fd("\nusage: cd [-L|-P] [dir]", STDERR_FILENO);
	}
	return (1);
}

int				cd_dir_error(char *newpwd, char *oldpwd, char *entry)
{
	struct stat	buffer;

	if (stat(newpwd, &buffer) == -1)
	{
		if (lstat(newpwd, &buffer) != -1)
			ft_putstr_fd_2("cd: too many levels of symbolic links: ", 2);
		else
			ft_putstr_fd("cd: no such file or directory: ", STDERR_FILENO);
	}
	else if (!S_ISDIR(buffer.st_mode))
		ft_putstr_fd("cd: not a directory: ", STDERR_FILENO);
	else
		ft_putstr_fd("cd: permission denied: ", STDERR_FILENO);
	ft_putendl_fd(entry, STDERR_FILENO);
	if (newpwd)
		free(newpwd);
	if (oldpwd)
		free(oldpwd);
	return (1);
}
