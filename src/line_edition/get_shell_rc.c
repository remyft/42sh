/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_rc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:16:30 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/18 11:58:00 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "shell_env.h"

void	launch_rc(t_s_env *e, int fd, char *path)
{
	char	*line;
	int		count;

	line = NULL;
	count = 1;
	while (get_next_line(fd, &line) > 0)
	{
		e->progname = ft_strjoin(path, ":");
		e->progname = ft_strjoinfree(e->progname, ft_itoa(count), 3);
		launch_new_cmd(&line, e);
		free(line);
		free(e->progname);
		count++;
	}
}

void	get_rc(t_s_env *e)
{
	char	*path;
	int		fd;
	char	*tmp_progname;

	tmp_progname = e->progname;
	if (!(path = getenv("HOME")))
		return ;
	path = ft_strjoin(path, "/");
	path = ft_strjoinfree(path, RC_NAME, 1);
	if ((fd = open(path, O_RDONLY | O_APPEND | O_CREAT, 0644)) < 0)
	{
		e->progname = tmp_progname;
		free(path);
		return ;
	}
	launch_rc(e, fd, path);
	free(path);
	e->progname = tmp_progname;
	close(fd);
}
