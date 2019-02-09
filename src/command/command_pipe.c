/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 06:58:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/09 07:08:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "command.h"
#include "shell_lib.h"
#include "shell_env.h"

static int		command_pipe_error(const char *err, t_s_env *e)
{
	ft_dprintf(STDERR_FILENO, "%s: %s failed\n", err, e->progname);
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
	ret = command_parse(cmd, &newe);
	sh_freetab(&newe.public_env);
	waitpid(pid, &ret, 0);
	exit(ret);
}

static int		command_pipe_child(int pfd[2], void *cmd, t_s_env *e)
{
	t_s_env		newe;
	int			ret;

	ft_memcpy(&newe, e, sizeof(newe));
	newe.public_env = sh_tabdup((const char **)e->public_env);
	newe.forked = 1;
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	ret = command_parse(cmd, &newe);
	sh_freetab(&newe.public_env);
	exit(ret);
}

int				command_pipe(void *cmd, t_s_env *e)
{
	pid_t		pid;
	int			ret;
	int			pfd[2];

	pid = 0;
	if (!((t_pipeline *)cmd)->left || !((t_pipeline *)cmd)->right)
		return (0);
	if (!e->forked && (pid = fork()) < 0)
		return (command_pipe_error("fork", e));
	if (pid == 0)
	{
		if (pipe(pfd) < 0)
			command_pipe_error("pipe", e);
		if ((pid = fork()) < 0)
			command_pipe_error("fork", e);
		else if (pid > 0)
			command_pipe_father(pid, pfd, ((t_pipeline *)cmd)->left, e);
		else
			command_pipe_child(pfd, ((t_pipeline *)cmd)->right, e);
	}
	else
		waitpid(pid, &ret, 0);
	return (0);
}
