/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 06:58:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/09 20:41:00 by gbourgeo         ###   ########.fr       */
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
	ft_dprintf(STDERR_FILENO, "%s: %s failed\n",e->progname, err);
	if (e->forked)
		exit(EXIT_FAILURE);
	return (1);
}

static int		command_pipe_father(pid_t pid, int pfd[2], void *cmd, t_s_env *e)
{
	t_s_env		newe;
	int			ret;

	ft_memcpy(&newe, e, sizeof(newe));
	newe.public_env = sh_tabdup((const char **)e->public_env);
	newe.forked = 1;
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	ret = command_parse(((t_pipeline *)cmd)->left, &newe);
	sh_freetab(&newe.public_env);
	close(STDOUT_FILENO);
	// waitpid(pid, &e->ret, 0);
	(void)pid;
	exit(e->ret);
}

static int		command_pipe_child(void *cmd, t_s_env *e, int pfd[2])
{
	t_s_env		newe;
	int			ret;

	ft_memcpy(&newe, e, sizeof(newe));
	newe.public_env = sh_tabdup((const char **)e->public_env);
	newe.forked = 1;
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	ret = command_parse(((t_pipeline *)cmd)->right, &newe);
	sh_freetab(&newe.public_env);
	exit(ret);
}

static int		command_pipeception(void *cmd, t_s_env *e, int pfc[2])
{
	pid_t		pid;
	// pid_t		pic;
	int			pfd[2];

	pid = 0;
		close(pfc[0]);
		dup2(pfc[1], STDOUT_FILENO);
		close(pfc[1]);
	if ((pid = fork()) < 0)
		return (command_pipe_error("fork", e));
	else if (pid == 0)
	{
		close(pfc[0]);
		dup2(pfc[1], STDOUT_FILENO);
		close(pfc[1]);
		if (pipe(pfd) < 0)
			command_pipe_error("pipe", e);
		if (*(int *)((t_pipeline *)cmd)->right == IS_A_PIPE)
			command_pipeception(((t_pipeline *)cmd)->right, e, pfd);
		else if ((pid = fork()) == 0)
			command_pipe_child(cmd, e, pfd);
		if (pid > 0)
			command_pipe_father(pid, pfd, cmd, e);
		command_pipe_error("fork", e);
	}
	else
		waitpid(pid, &e->ret, 0);
	(void)pfc;
	// if (pipe(pfd) < 0)
	// 	command_pipe_error("pipe", e);
	// // else if ((pid = fork()) < 0)
	// // 	return (command_pipe_error("fork", e));
	// // else if (pid == 0)
	// if ((pid = fork()) == 0)
	// 	command_pipe_child(cmd, e, pfd);
	// else if (pid > 0)
	// {
	// 	command_pipe_father(pid, pfd, cmd, e);
	// }
	exit(e->ret);
}

int				command_pipe(void *cmd, t_s_env *e)
{
	pid_t		pid;
	int			pfd[2];

	pid = 0;
	if ((pid = fork()) < 0)
		return (command_pipe_error("fork", e));
	else if (pid == 0)
	{
		if (pipe(pfd) < 0)
			command_pipe_error("pipe", e);
		if (*(int *)((t_pipeline *)cmd)->right == IS_A_PIPE)
			command_pipeception(((t_pipeline *)cmd)->right, e, pfd);
		else if ((pid = fork()) == 0)
			command_pipe_child(cmd, e, pfd);
		if (pid > 0)
			command_pipe_father(pid, pfd, cmd, e);
		command_pipe_error("fork", e);
	}
	else
		waitpid(pid, &e->ret, 0);
	ft_dprintf(1,"ret:%d\n",e->ret);
	return (0);
	// if ((pic = fork()) < 0)
	// 	return (command_pipe_error("fork", e));
	// else if (pic == 0)
	// 	command_pipe_father(pid, pfd, cmd, e);
	// else
	// 	waitpid(pic, &e->ret, 0);
	// ft_dprintf(1,"ret:%d\n",e->ret);
	// return (0);
}
