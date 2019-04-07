/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 06:58:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/07 16:50:12 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "ft_dprintf.h"
#include "command.h"
#include "shell_lib.h"
#include "shell_env.h"
#include "job_control.h"
#include "command_error.h"

void		close_unexpected_fd(int *fds)
{
	if (fds[FD_STDIN] != STDIN_FILENO && fds[FD_STDIN] != STDOUT_FILENO
			&& fds[FD_STDIN] != STDERR_FILENO)
		close(fds[FD_STDIN]);
	if (fds[FD_STDOUT] != STDIN_FILENO && fds[FD_STDOUT] != STDOUT_FILENO
			&& fds[FD_STDOUT] != STDERR_FILENO)
		close(fds[FD_STDOUT]);
	if (fds[FD_STDERR] != STDIN_FILENO && fds[FD_STDERR] != STDOUT_FILENO
			&& fds[FD_STDERR] != STDERR_FILENO)
		close(fds[FD_STDERR]);
}

int		command_pipe_dup(t_jobs *job, t_process *p, t_s_env *e, int *fds)
{
	fds[FD_STDERR] = p->fds[2];
	if (p->next)
	{
		if (pipe(fds) < 0)
			return (command_error(e->progname, 10, NULL, e));
		fds[FD_STDOUT] = fds[FD_PIPE_OUT];
	}
	else
		fds[FD_STDOUT] = p->fds[1];
	p->pipe[0] = fds[0];
	p->pipe[1] = fds[1];
	if (p->fds[0] == STDIN_FILENO)
		p->fds[0] = fds[FD_STDIN];
	if (p->fds[1] == STDOUT_FILENO)
		p->fds[1] = fds[FD_STDOUT];
	if (p->fds[2] == STDERR_FILENO)
		p->fds[2] = fds[FD_STDERR];
	return (command_check(job, p, e));
}
