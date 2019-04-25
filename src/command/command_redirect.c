/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:10:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/24 16:48:08 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"
#include "command.h"
#include "command_error.h"
#include <stdio.h>

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
		p->fds[1] = fdarg;
		if (r->fdio != fdio)
			close(fdio);
		if (fdarg > 0 && r->fdarg != fdarg)
			close(fdarg);
		r = r->next;
	}
	return (ERR_OK);
}

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
		printf("fdarg : %d\n", fdarg);
		printf("fdio : %d\n", fdio);
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
