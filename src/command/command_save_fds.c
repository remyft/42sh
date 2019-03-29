/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_save_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:58:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/01 12:59:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int				command_save_fds(int fd, int fds[3])
{
	if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO)
		if (fds[fd] == 0)
			if ((fds[fd] = fcntl(fd, F_DUPFD_CLOEXEC, 10)) < 0)
				return (1);
	return (0);
}
