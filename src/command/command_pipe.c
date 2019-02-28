/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 06:58:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/28 23:09:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "ft_dprintf.h"
#include "command.h"
#include "shell_lib.h"
#include "shell_env.h"

static int		command_pipe_error(const char *err, t_s_env *e)
{
	ft_dprintf(STDERR_FILENO, "%s: %s failed\n", e->progname, err);
	if (e->forked)
		exit(EXIT_FAILURE);
	return (1);
}

static int		command_pipe_left(void *cmd, t_s_env *e, int pfd[2])
{
	t_s_env		newe;

	ft_memcpy(&newe, e, sizeof(newe));
	newe.public_env = sh_tabdup((const char **)e->public_env);
	newe.private_env = sh_tabdup((const char **)e->private_env);
	newe.forked = 1;
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	command_parse(((t_pipeline *)cmd)->left, &newe);
	close(STDOUT_FILENO);
	sh_freetab(&newe.public_env);
	sh_freetab(&newe.private_env);
	exit(newe.ret);
}

static int		command_pipe_right(void *cmd, t_s_env *e, int pfd[2])
{
	t_s_env		newe;

	ft_memcpy(&newe, e, sizeof(newe));
	newe.public_env = sh_tabdup((const char **)e->public_env);
	newe.private_env = sh_tabdup((const char **)e->private_env);
	newe.forked = 1;
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	command_parse(((t_pipeline *)cmd)->right, &newe);
	close(STDIN_FILENO);
	sh_freetab(&newe.public_env);
	sh_freetab(&newe.private_env);
	exit(newe.ret);
}

static int		command_last_pipe(int pfd[2], t_pipeline *cmd, t_s_env *e)
{
	pid_t		pid;
	t_command	*arg;

	e->forked = 1;
	close(pfd[1]);
	if ((pid = fork()) < 0)
		return (command_pipe_error("fork", e));
	else if (pid == 0)
		command_pipe_right(cmd, e, pfd);
	e->forked = 0;
	arg = (t_command *)((t_pipeline *)cmd)->right;
	command_wait(pid, arg->args->async, &e->ret);
	close(pfd[0]);
	return (0);
}

int				command_pipe(void *cmd, t_s_env *e)
{
	pid_t		pid;
	int			pfd[2];
	t_command	*arg;

	if (pipe(pfd) < 0)
		return (command_pipe_error("pipe", e));
	e->forked = 1;
	if ((pid = fork()) < 0)
		return (command_pipe_error("fork", e));
	else if (pid == 0)
		command_pipe_left(cmd, e, pfd);
	e->forked = 0;
	if (*(int *)((t_pipeline *)cmd)->right == IS_A_PIPE)
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
		if (command_pipe(((t_pipeline *)cmd)->right, e))
			return (1);
	}
	else if (command_last_pipe(pfd, cmd, e))
		return (1);
	// char buf[512];
	// if (read(0, buf, 512) <= 0)
	// 	printf("read failed\n");
	arg = (t_command *)((t_pipeline *)cmd)->left;
	command_wait(pid, arg->args->async, NULL);
	ft_dprintf(2,"[%s] ret = %d\n", arg->args->cmd[0], e->ret);
	return (0);
}
