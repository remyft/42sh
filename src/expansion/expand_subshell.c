/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:24:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/28 01:42:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "shell_lib.h"
#include "expansion.h"
#include "expansion_errors.h"

int				expand_subshell(t_exp *param, t_ret *ret)
{
	size_t		i;
	size_t		depth;
	char		*line;
	int			fd[2];
	int			save;
	pid_t		pid;

	depth = 0;
	i = param->i + 1;
	while (param->buff[i] != ')' || --depth)
	{
		if (param->buff[i] == '(')	
			++depth;
		i++;
	}
	line = sh_strnjoin(param->buff + param->i + 2, "\n", i - param->i - 2);
	if (!line)
		return (ERR_MALLOC);
	if (pipe(fd) < 0)
		return (ERR_PIPE);
	if ((pid = fork()) < 0)
		return (ERR_FORK);
	else if (pid == 0)
	{
		t_s_env		newe;

		if ((save = fcntl(STDIN_FILENO, F_DUPFD_CLOEXEC, 10)) < 0)
			return (ERR_FCNTL);

		ft_memcpy(&newe, param->e, sizeof(newe));
		newe.public_env = sh_tabdup((const char **)param->e->public_env);
		newe.private_env = sh_tabdup((const char **)param->e->private_env);
		newe.forked = 1;
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		launch_new_cmd(&line, &newe);
		close(STDOUT_FILENO);
		sh_freetab(&newe.public_env);
		sh_freetab(&newe.private_env);
		exit(newe.ret);
	}
	else
	{
		char		buff[1024];
		int			val;

		close(fd[1]);
		waitpid(pid, &param->e->ret, 0);
		while ((val = read(fd[0], buff, sizeof(buff) - 1)) > 0)
		{
			buff[val] = '\0';
			if (!ret->substitute)
				ret->substitute = ft_strdup(buff);
			else
				ret->substitute = ft_strjoinfree(ret->substitute, buff, 1);
		}
		printf("subs: %s\n", ret->substitute);
	}
	return (ERR_NONE);
}
