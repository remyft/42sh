/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_rc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:16:30 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/03 20:53:46 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "shell_env.h"
#include "shell_lib.h"

void	launch_rc(t_s_env *e, int fd)
{
	char	*line;

	line = sh_get_file(fd);
	if (line)
	{
		launch_new_cmd(&line, e);
		ft_strdel(&line);
	}
}

void	get_rc(t_s_env *e, char *relative)
{
	char	*path;
	int		fd;
	char	*tmp_progname;

	tmp_progname = e->progname;
	if (!relative)
	{
		if (!(path = getenv("HOME")))
			return ;
		path = ft_strjoin(path, "/");
		path = ft_strjoinfree(path, RC_NAME, 1);
	}
	else
		path = ft_strdup(relative);
	if ((fd = open(path, O_RDONLY | O_CREAT, 0644)) < 0)
	{
		free(path);
		return ;
	}
	e->progname = path;
	launch_rc(e, fd);
	free(path);
	e->progname = tmp_progname;
	close(fd);
}
