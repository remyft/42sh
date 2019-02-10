/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 06:58:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/10 17:32:27 by gbourgeo         ###   ########.fr       */
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

static int		command_pipe_father(void *cmd, t_s_env *e, t_pipe *p, pid_t pid)
{
	t_s_env		newe;

	ft_memcpy(&newe, e, sizeof(newe));
	newe.public_env = sh_tabdup((const char **)e->public_env);
	newe.forked = 1;
	close(p->pfd[0]);
	dup2(p->pfd[1], STDOUT_FILENO);
	close(p->pfd[1]);
	command_parse(((t_pipeline *)cmd)->left, &newe);
	sh_freetab(&newe.public_env);
	close(STDOUT_FILENO);
	waitpid(pid, &p->ret, 0);
	exit(p->ret);
}

static int		command_pipe_child(void *cmd, t_s_env *e, t_pipe *p)
{
	t_s_env		newe;

	ft_memcpy(&newe, e, sizeof(newe));
	newe.public_env = sh_tabdup((const char **)e->public_env);
	newe.forked = 1;
	close(p->pfd[1]);
	dup2(p->pfd[0], STDIN_FILENO);
	close(p->pfd[0]);
	p->ret = command_parse(((t_pipeline *)cmd)->right, &newe);
	sh_freetab(&newe.public_env);
	exit(p->ret);
}

static int		command_pipeception(void *cmd, t_s_env *e, t_pipe *p)
{
	pid_t		pid;

	close(p->pfd[1]);
	dup2(p->pfd[0], STDIN_FILENO);
	close(p->pfd[0]);
	if ((pid = fork()) < 0)
		return (command_pipe_error("fork", e));
	else if (pid == 0)
	{
		if (pipe(p->pfd) < 0)
			command_pipe_error("pipe", e);
		if ((pid = fork()) == 0)
		{
			if (*(int *)((t_pipeline *)cmd)->right == IS_A_PIPE)
				command_pipeception(((t_pipeline *)cmd)->right, e, p);
			command_pipe_child(cmd, e, p);
		}
		else if (pid < 0)
			command_pipe_error("fork", e);
		command_pipe_father(cmd, e, p, pid);
	}
	waitpid(pid, &p->ret, 0);
	exit(p->ret);
}

int				command_pipe(void *cmd, t_s_env *e)
{
	pid_t		pid;
	t_pipe		p;

	ft_memset(&p, 0, sizeof(p));
	if ((pid = fork()) < 0)
		return (command_pipe_error("fork", e));
	else if (pid == 0)
	{
		e->forked = 1;
		if (pipe(p.pfd) < 0)
			command_pipe_error("pipe", e);
		if ((pid = fork()) == 0)
		{
			if (*(int *)((t_pipeline *)cmd)->right == IS_A_PIPE)
				command_pipeception(((t_pipeline *)cmd)->right, e, &p);
			command_pipe_child(cmd, e, &p);
		}
		else if (pid < 0)
			command_pipe_error("fork", e);
		command_pipe_father(cmd, e, &p, pid);
	}
	waitpid(pid, &p.ret, 0);
	// ft_dprintf(2,"ret:%d\n",p.ret);
	return (0);
}
