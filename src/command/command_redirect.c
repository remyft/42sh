/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:10:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/01 13:03:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"
#include "command.h"

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
