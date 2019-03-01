/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 20:23:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/01 17:33:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

static int		command_ret(int *ret)
{
	if (!ret)
		return (0);
	if (WIFEXITED(*ret))
		*ret = WEXITSTATUS(*ret);
	else if (WIFSIGNALED(*ret))
		*ret = WTERMSIG(*ret) + 128;
	else if (WIFSTOPPED(*ret))
		*ret = WTERMSIG(*ret) + 128;
	return (0);
}

int				command_wait(pid_t pid, int async, int *ret)
{
	pid_t		got;

	if (!async)
		while ((got = waitpid(pid, ret, 0)) > 0)
			if (got == pid)
				return (command_ret(ret));
	return (1);
}
