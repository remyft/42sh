/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/08 03:13:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "shell_lib.h"
#include "command.h"

static int		command_pipe(void *cmd, t_s_env *e)
{
	pid_t		pid;
	int			ret;
	int			pfd[2];

	pid = 0;
	if (!((t_pipeline *)cmd)->left || !((t_pipeline *)cmd)->right)
		return (0);
	if (!e->forked && (pid = fork()) < 0)
	{
		ft_dprintf(STDERR_FILENO, "%s: fork failed\n", e->progname);
		return (1);
	}
	if (pid == 0)
	{
		if (pipe(pfd) < 0)
		{
			ft_dprintf(STDERR_FILENO, "%s: pipe failed\n", e->progname);
			exit(EXIT_FAILURE);
		}
		if ((pid = fork()) < 0)
		{
			ft_dprintf(STDERR_FILENO, "%s: fork failed\n", e->progname);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
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
			exit(ret);
		}
		else
		{
			t_s_env		newe;
			int			ret;

			ft_memcpy(&newe, e, sizeof(newe));
			newe.public_env = sh_tabdup((const char **)e->public_env);
			newe.forked = 1;
			close(pfd[1]);
			dup2(pfd[0], STDIN_FILENO);
			close(pfd[0]);
			ret = command_parse(((t_pipeline *)cmd)->right, e);
			sh_freetab(&newe.public_env);
			exit(ret);
		}
	}
	else
		waitpid(pid, &ret, 0);
	return (0);
}

int				command_parse(void *cmd, t_s_env *e)
{
	t_execute	exec;

	command_debug(cmd);
	if (*(int *)cmd == IS_A_PIPE)
		return (command_pipe(cmd, e));
	ft_memset(&exec, 0, sizeof(exec));
	if (!((t_command *)cmd)->args)
		return (0);
	exec.variable = ((t_command *)cmd)->args;
	exec.redirection = ((t_command *)cmd)->redir;
	return (command_prepare(&exec, e));
}
