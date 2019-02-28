/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 06:58:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/28 13:50:54 by dbaffier         ###   ########.fr       */
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

void			*command_pipeception(void *cmd, t_s_env *e, void *right)
{
	t_command	*arg;
	pid_t		pid;
	int			pfd[2];

	if (*(int *)((t_pipeline *)right)->right == IS_A_PIPE)
		cmd = command_pipeception(cmd, e, ((t_pipeline *)right)->right);
	if (pipe(pfd) < 0)
		command_pipe_error("pipe", e);
	if ((pid = fork()) < 0)
		command_pipe_error("fork", e);
	else if (pid == 0)
		command_pipe_left(cmd, e, pfd);
	arg = (t_command *)((t_pipeline *)cmd)->left;
	command_wait(pid, arg->args->async, NULL);
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	return (((t_pipeline *)cmd)->right);
}

int				command_pipe(void *cmd, t_s_env *e)
{
	t_command	*arg;
	pid_t		pid;
	int			pfd[2];

	e->forked = 1;
	if (*(int *)((t_pipeline *)cmd)->right == IS_A_PIPE)
		cmd = command_pipeception(cmd, e, ((t_pipeline *)cmd)->right);
	arg = (t_command *)((t_pipeline *)cmd)->right;
	if ((pid = fork()) < 0)
		return (command_pipe_error("fork", e));
	else if (pid == 0)
	{
		if (pipe(pfd) < 0)
			command_pipe_error("pipe", e);
		if ((pid = fork()) < 0)
			command_pipe_error("fork", e);
		else if (pid == 0)
			command_pipe_left(cmd, e, pfd);
		arg = (t_command *)((t_pipeline *)cmd)->left;
		command_wait(pid, arg->args->async, NULL);
		command_pipe_right(cmd, e, pfd);
	}
	command_wait(pid, arg->args->async, &e->ret);
	printf("[%s] async:%d - ret:%d\n", arg->args->cmd[0], arg->args->async, e->ret);
	e->forked = 0;
	return (0);
}
