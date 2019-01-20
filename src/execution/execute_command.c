/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 01:26:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/20 02:20:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execution.h"

// static int		fork_error(const char *err, t_s_env *e)
// {
// 	ft_putstr_fd(e->progname, STDERR_FILENO);
// 	ft_putstr_fd(": ", STDERR_FILENO);
// 	ft_putstr_fd(err, STDERR_FILENO);
// 	return (1);
// }

int				execute_command(const char *buff, void *cmd, t_s_env *e)
{
	// pid_t		pid;

	// pid = fork();
	// if (pid < 0)
	// 	return (fork_error("fork failed.", e));
	// if (pid == 0)
	// {
	// 	ft_putendl("TSA !");
	// 	exit(1);
	// }
	// waitpid(pid, &e->ret, 0);
	debug_execution(cmd);
	if (*(int *)cmd == IS_A_PIPE)
		;
	(void)buff;
	(void)e;
	return (0);
}
