/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:10:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 11:04:33 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"
#include "command.h"
#include "command_error.h"
#include <stdio.h>

/*
static void		command_set_s_fds(int *fd, int *fdc, int std, int new_fd)
{
	if (fdc)
		if (new_fd == std && *fdc == -1)
			new_fd = -1;
	if (*fd != STDIN_FILENO && *fd != STDOUT_FILENO && *fd != STDERR_FILENO)
		close(*fd);
	*fd = new_fd;
}

static void		command_set_fds(t_process *p, int fdarg, int fdio)
{
	if (!(fdarg == STDIN_FILENO && (fdio == STDOUT_FILENO || fdio == STDERR_FILENO)))
	{
		if (fdio == STDIN_FILENO)
			command_set_s_fds(&p->fds[0], NULL, STDIN_FILENO, fdarg);
		if (fdio == STDOUT_FILENO)
			command_set_s_fds(&p->fds[1], &p->fds[2], STDERR_FILENO, fdarg);
		if (fdio == STDERR_FILENO)
			command_set_s_fds(&p->fds[2], &p->fds[1], STDOUT_FILENO, fdarg);
	}
}

int				command_redirect_test(t_process *p)
{
	int				fdarg;
	int				fdio;
	t_execute		*e;
	t_redirection	*r;

	e = (t_execute *)p->exec;
	r = e->redirection;
	while (r)
	{
		fdarg = GET_FD(r->fdarg);
		fdio = GET_FD(r->fdio);
		if (command_save_fds(fdarg, e->fds) || command_save_fds(fdio, e->fds))
			return (ERR_FCNTL);
		command_set_fds(p, fdarg, fdio);
	//	printf("fdarg : %d -- fdio : %d\n", fdarg, fdio);
		//if (r->fdio != fdio)
			//close(fdio);
	//	if (fdarg > 0 && r->fdarg != fdarg)
		//	close(fdarg);
		r = r->next;
	}
	return (ERR_OK);
}*/

int				command_redirect(int fds[3], t_redirection *redir)
{
	int			fdarg;
	int			fdio;

	ft_memset(fds, 0, 3);
	while (redir)
	{
		fdarg = GET_FD(redir->fdarg);
		fdio = GET_FD(redir->fdio);
		if (command_save_fds(fdarg, fds) || command_save_fds(fdio, fds))
			return (ERR_FCNTL);
		if (fdarg > 0 && dup2(fdarg, fdio) < 0)
			return (ERR_DUP2);
		if (redir->fdio != fdio)
			close(fdio);
		if (fdarg > 0 && redir->fdarg != fdarg)
			close(fdarg);
		redir = redir->next;
	}
	return (ERR_OK);
}
