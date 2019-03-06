/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 20:23:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/06 13:23:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>

static void		command_ret(int *ret)
{
	if (!ret)
		return ;
	if (WIFEXITED(*ret))
		*ret = WEXITSTATUS(*ret);
	else if (WIFSIGNALED(*ret))
	{
		*ret = WTERMSIG(*ret) + 128;
		// if (WTERMSIG(*ret) == SIGINT)
			write(1, "\n", 1);
	}
	else if (WIFSTOPPED(*ret))
		*ret = WTERMSIG(*ret) + 128;
}

void			command_wait(pid_t pid, int async, int *ret)
{
	pid_t		got;

	if (!async)
		while ((got = waitpid(pid, ret, 0)) > 0)
			if (got == pid)
				return (command_ret(ret));
}
