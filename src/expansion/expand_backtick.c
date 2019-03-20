/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_backtick.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 03:51:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:49:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "expansion_loop.h"
#include "expansion_errors.h"

static size_t	get_line_length(const char *line)
{
	size_t		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
			i++;
		else if (line[i] == '`')
			break ;
		i++;
	}
	return (i);
}

static void		expand_subshell_child(int pfd[2], size_t i, t_exp *param)
{
	t_s_env		newe;
	char		*line;

	ft_memcpy(&newe, param->e, sizeof(newe));
	newe.public_env = sh_tabdup((const char **)param->e->public_env);
	newe.private_env = sh_tabdup((const char **)param->e->private_env);
	newe.forked = 0;
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	line = ft_strndup((char *)param->buff + param->i + 1, i - param->i);
	if (line)
		launch_new_cmd(&line, &newe);
	close(STDOUT_FILENO);
	sh_freetab(&newe.public_env);
	sh_freetab(&newe.private_env);
	sh_freestr(&line);
	exit(newe.ret);
}

int				expand_backtick(t_exp *param, t_ret *ret)
{
	int			pfd[2];
	pid_t		pid;
	size_t		i;

	i = get_line_length(param->buff + param->i + 1) + param->i;
	if (pipe(pfd) < 0)
		return (ERR_PIPE);
	if ((pid = fork()) < 0)
		return (ERR_FORK);
	else if (pid == 0)
		expand_subshell_child(pfd, i, param);
	else
		expand_subshell_father(pfd, pid, param, ret);
	param->i = i + 1;
	return (ERR_NONE);
}
