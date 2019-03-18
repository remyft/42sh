/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_source.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 20:58:41 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/18 22:57:34 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "builtin_source.h"
#include "ft_dprintf.h"
#include "shell.h"

int		builtin_source_access(char *path)
{
	struct stat	buf;

	if (!path)
		return (ERR_MALLOC);
	if (access(path, F_OK))
		return (ERR_NO_SUCH_FILE);
	if (access(path, R_OK))
		return (ERR_PERMISSION);
	if (stat(path, &buf))
		return (ERR_NO_SUCH_FILE);
	if (S_ISDIR(buf.st_mode))
		return (ERR_IS_DIR);
	return (ERR_OK);
}

int		source_error(int err, char *path, char **absolute)
{
	static char *errors[] = {
		NULL, "is a directory", "not enough argument",
		"no such file or directory", "permission denied", "malloc failed",
		"file not found",
	};

	if (absolute && *absolute)
		free(*absolute);
	if (err == ERR_NOT_ARG)
		ft_dprintf(STDERR_FILENO, "source: %s\n", errors[err]);
	else
		ft_dprintf(STDERR_FILENO, "source: %s: %s\n", path, errors[err]);
	return (1);
}

int		builtin_source(t_execute *exec, t_s_env *e)
{
	char	*path;
	int		fd;
	int		err;
	char	*pwd;

	if (!exec->cmd[1])
		return (source_error(ERR_NOT_ARG, exec->cmd[0], NULL));
	if (exec->cmd[1][0] != '/')
	{
		if (!(pwd = getenv("PWD")))
			return (source_error(ERR_NOT_FOUND, exec->cmd[1], NULL));
		if (*(ft_strchr(pwd, 0) - 1) != '/')
			path = ft_strjoin(pwd, "/");
		else
			path = ft_strdup(pwd);
		path = ft_strjoinfree(path, exec->cmd[1], 1);
	}
	else
		path = ft_strdup(exec->cmd[1]);
	if ((err = builtin_source_access(path)) != ERR_OK)
		return (source_error(err, exec->cmd[1], &path));
	if ((fd = open(path, O_RDONLY)) < 0)
		return (source_error(ERR_NOT_FOUND, exec->cmd[1], &path));
	launch_rc(e, fd, path);
	free(path);
	return (0);
}
