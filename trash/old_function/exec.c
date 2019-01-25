/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:15:36 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 02:48:54 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"

static char	*get_path(char **env, char *cmd)
{
	char		*toget;
	char		*path;
	int			j;
	struct stat	stat;

	j = 0;
	toget = get_env(env, "PATH");
	while (1)
	{
		path = strdup_until(&toget[j], ':');
		path = ft_strjoinfree(path, "/", 1);
		path = ft_strjoinfree(path, cmd, 1);
		if (lstat(path, &stat) != -1)
			return (ft_free(toget, path));
		free(path);
		if (!ft_occuc(&toget[j], ':'))
			return (ft_free(toget, NULL));
		j += !(toget[j + ft_strlen_ch(toget, ':')])
			? ft_strlen_ch(&toget[j], ':') : ft_strlen_ch(&toget[j], ':') + 1;
	}
	return (NULL);
}

int			ft_exec(char **env, char **cmd, struct termios *save)
{
	pid_t	pid;
	char	*path;
	int		status;

	if (cmd[0][0] != '/')
	{
		if (!(path = get_path(env, cmd[0])))
			return (0);
		free(cmd[0]);
		cmd[0] = ft_strdup(path);
		free(path);
	}
	term_restore(*save);
	pid = fork();
	if (pid < 0)
	{
		ft_putendl("Something happend, fork failed.");
		return (0);
	}
	else if (pid == 0)
	{
		execve(cmd[0], cmd, env);
		free_tab(&env);
		free_tab(&cmd);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	define_new_term(save);
	return (1);
}
