/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:24:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/02 15:34:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "shell_lib.h"
#include "command.h"
#include "expansion.h"
#include "expansion_errors.h"

static size_t	get_line_length(const char *line)
{
	size_t		i;
	size_t		depth;
	char		quote;

	i = 0;
	depth = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			if (!quote)
				quote = line[i];
			else if (quote == '\'')
				quote = 0;
		}
		else if (line[i] == '"')
		{
			if (!quote)
				quote = line[i];
			else if (quote == '"')
				quote = 0;
		}
		else if (line[i] == '\\')
			i++;
		else if (!quote && line[i] == '(')
			++depth;
		else if (!quote && line[i] == ')')
			if (--depth == 0)
				break ;
		i++;
	}
	return (i);
}

int				expand_subshell(t_exp *param, t_ret *ret)
{
	int			pfd[2];
	pid_t		pid;

	if (pipe(pfd) < 0)
		return (ERR_PIPE);
	if ((pid = fork()) < 0)
		return (ERR_FORK);
	else if (pid == 0)
	{
		t_s_env		newe;
		size_t		i;
		char		*line;

		ft_memcpy(&newe, param->e, sizeof(newe));
		newe.public_env = sh_tabdup((const char **)param->e->public_env);
		newe.private_env = sh_tabdup((const char **)param->e->private_env);
		newe.forked = 1;
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		i = get_line_length(param->buff + param->i + 1) + param->i + 1;
		line = sh_strnjoin(param->buff + param->i + 2, "\n", i - param->i - 2);
		if (line)
			launch_new_cmd(&line, &newe);
		close(STDOUT_FILENO);
		sh_freetab(&newe.public_env);
		sh_freetab(&newe.private_env);
		sh_freestr(&line);
		exit(newe.ret);
	}
	else
	{
		char		buff[1024];
		int			i;

		close(pfd[1]);
		command_wait(pid, 0, &param->e->ret);
		while ((i = read(pfd[0], buff, sizeof(buff) - 1)) > 0)
		{
			buff[i] = '\0';
			if (!ret->substitute)
				ret->substitute = ft_strdup(buff);
			else
				ret->substitute = ft_strjoinfree(ret->substitute, buff, 1);
		}
		close(pfd[0]);
		i = 0;
		if (ret->substitute)
			while (ret->substitute[i])
			{
				if (ret->substitute[i] == '\n')
					ret->substitute[i] = ' ';
				i++;
			}
		// printf("word: %s\n", ret->word);
		printf("subs: %s\n", ret->substitute);
		sh_freestr(&ret->word);
		ret->w_len = 0;
		ret->w_max = 0;
		param_addstr(ret->substitute, ret);
		sh_freestr(&ret->substitute);
	}
	return (ERR_NONE);
}
