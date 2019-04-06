/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_source.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 20:58:41 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/06 20:29:11 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "builtin_source.h"
#include "ft_dprintf.h"
#include "shell.h"
#include "builtins.h"

static int	builtin_source_access(char *path)
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

static int	source_error(int err, char **cmd, char **absolute)
{
	static char *errors[] = {
		NULL, "is a directory", "not enough argument",
		"no such file or directory", "permission denied", "malloc failed",
		"file not found",
	};

	if (absolute && *absolute)
		free(*absolute);
	if (err == ERR_NOT_ARG)
		ft_dprintf(STDERR_FILENO, "%s: %s\n", cmd[0], errors[err]);
	else
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", cmd[0], cmd[1], errors[err]);
	return (1);
}

static char	*get_path(t_execute *exec)
{
	char	*path;

	if (exec->cmd[1][0] != '/')
	{
		if (!(path = getenv("PWD")))
			return (NULL);
		path = (*(ft_strchr(path, 0) - 1) != '/') ? ft_strjoin(path, "/")
			: ft_strdup(path);
		path = ft_strjoinfree(path, exec->cmd[1], 1);
	}
	else
		path = ft_strdup(exec->cmd[1]);
	return (path);
}

int			builtin_source(t_execute *exec, t_s_env *e)
{
	char	*path;
	int		fd;
	int		err;
	char	*tmp_progname;

	tmp_progname = e->progname;
	if (!exec->cmd[1])
		return (source_error(ERR_NOT_ARG, exec->cmd, NULL));
	if (!(path = get_path(exec)))
		return (source_error(ERR_NOT_FOUND, exec->cmd, NULL));
	if ((err = builtin_source_access(path)) != ERR_OK)
		return (source_error(err, exec->cmd, &path));
	if ((fd = open(path, O_RDONLY)) < 0)
		return (source_error(ERR_PERMISSION, exec->cmd, &path));
	e->progname = path;
	launch_rc(e, fd);
	close(fd);
	free(path);
	e->progname = tmp_progname;
	return (0);
}
