/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 06:58:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/28 12:11:35 by gbourgeo         ###   ########.fr       */
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

// void			*command_pipeception(void *cmd, t_s_env *e, t_pid **pid)
// {
// 	t_command	*arg;

// 	if (!(*pid = new_pid(cmd, *pid)))
// 		return (command_pipe_error("malloc", e));
// 	if (*(int *)((t_pipeline *)cmd)->right == IS_A_PIPE)
// 		cmd = command_pipeception(((t_pipeline *)cmd)->right, e, pid);
// 	if (pipe((*pid)->pfd) < 0)
// 		command_pipe_error("pipe", e);
// 	if (((*pid)->pid = fork()) < 0)
// 		command_pipe_error("fork", e);
// 	else if ((*pid) == 0)
// 		command_pipe_left(cmd, e, (*pid)->pfd);
// 	arg = (t_command *)((t_pipeline *)cmd)->left;
// 	command_wait(pid, arg->args->async, NULL);
// 	close(pfd[1]);
// 	dup2(pfd[0], STDIN_FILENO);
// 	close(pfd[0]);
// 	return (((t_pipeline *)cmd)->right);
// 	}
// 	command_wait(pid, arg->args->async, &e->ret);
// 	return (((t_pipeline *)cmd)->right);
// }

static t_pid	*new_pid(t_pipeline *cmd, t_pid *next)
{
	t_pid		*pid;

	if (!(pid = ft_memalloc(sizeof*pid)))
		return (NULLPID);
	pid->cmd = cmd;
	pid->next = next;
	if (next)
		next->prev = pid;
	return (pid);
}

static t_pid	*get_pid(t_pid *pid_set)
{
	while (pid_set)
		if (pid_set->cmd->args->async == 0)
			return (pid_set);
		else
			pid_set = pid_set->next;
	return (NULLPID);
}

static int		command_waitpid(t_pid *pid_set, int *ret)
{
	pid_t		got;
	t_pid		*tmp;

	while ((tmp = get_pid(pid_set)))
	{
		while ((got = waitpid(pid_set->pid, ret, 0)) > 0)
			if (got == pid_set->pid)
				return (0);
	}
	return (1);
}

int				command_pipe(void *cmd, t_s_env *e)
{
	t_pid		*pid_set;
	int			pfd[2];

	if (!(pid_set = new_pid(((t_pipeline *)cmd)->left, NULLPID)))
		return (command_pipe_error("malloc", e));
	if ((pid_set->pid = fork()) < 0)
		return (command_pipe_error("fork", e));
	else if (pid_set->pid == 0)
	{
		e->forked = 1;
		// if (*(int *)((t_pipeline *)cmd)->right == IS_A_PIPE)
		// 	cmd = command_pipeception(((t_pipeline *)cmd)->right, e, &pid_set);
		if (!(pid_set = new_pid(cmd, &pid_set)))
			command_pipe_error("malloc", e);
		if (pipe(pfd) < 0)
			command_pipe_error("pipe", e);
		if (!(pid_set = new_pid(((t_pipeline *)cmd)->right, &pid_set)))
			command_pipe_error("malloc", e);
		if ((pid_set->pid = fork()) < 0)
			command_pipe_error("fork", e);
		else if (pid_set->pid == 0)
			command_pipe_left(cmd, e, pfd);
		command_pipe_right(cmd, e, pfd);
	}
	command_waitpid(pid_set, &e->ret);
	printf("[%s] async:%d - ret:%d\n", arg->args->cmd[0], arg->args->async, e->ret);
	e->forked = 0;
	return (0);
}
