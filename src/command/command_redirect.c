/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:10:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/07 22:02:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"
#include "shell_env.h"

static int		command_save_fds(int fd, int fds[3])
{
	if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO)
		if (fds[fd] == 0)
			if ((fds[fd] = fcntl(fd, F_DUPFD_CLOEXEC, 10)) < 0)
				return (1);
	return (0);
}

int				command_redirect(int fds[3], t_redirection *redir, t_s_env *e)
{
	int			fdarg;
	int			fdio;

	ft_memset(fds, 0, 3);
	while (redir)
	{
		fdarg = GET_FD(redir->fdarg);
		fdio = GET_FD(redir->fdio);
		if (command_save_fds(fdarg, fds) || command_save_fds(fdio, fds))
			return (redirect_error(1, "FCNTL", e));
		if (fdarg > 0 && dup2(fdarg, fdio) < 0)
			return (redirect_error(0, "DUP2", e));
		if (redir->fdio != fdio)
			close(fdio);
		if (fdarg > 0 && redir->fdarg != fdarg)
			close(fdarg);
		redir = redir->next;
	}
	return (0);
}
