/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:53:59 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/11 08:05:20 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		cmp_strpart(char *src, char *str, int *beg)
{
	int i;

	i = 0;
	while (src[i] && src[i] == str[*beg] && src[i] != '=')
	{
		i++;
		*beg += 1;
	}
	if (src[i] == '=')
		if (!str[*beg] || !ft_isalnum(str[*beg]))
			return (i);
	return (0);
}

char	*test_var(char **env, char *cmd)
{
	int		beg;
	int		end;
	int		to_cp;
	int		i;
	char	*ret;

	beg = 0;
	while (cmd[beg] != '$')
		beg++;
	beg++;
	i = 0;
	while (env[i])
	{
		end = beg;
		if ((to_cp = cmp_strpart(env[i], cmd, &end)))
		{
			ret = ft_strnew(to_cp + 2);
			ret[0] = '$';
			ft_strncpy(ret + 1, env[i], to_cp);
			ret[to_cp + 1] = '\0';
			return (ret);
		}
		i++;
	}
	return (NULL);
}

int		get_var(char **env, char **cmd)
{
	int		i;
	char	*tmp;
	char	*var;
	char	*rep;

	i = -1;
	while (cmd[++i])
		if (ft_occuc(cmd[i], '$'))
		{
			if (!(tmp = test_var(env, cmd[i])))
			{
				ft_putend(ft_strstr(cmd[i], "$"), " : Undefined variable.\n");
				return (0);
			}
			else
			{
				var = ft_strdup(cmd[i]);
				free(cmd[i]);
				cmd[i] = replace_str(var, tmp, (rep = get_env(env, &tmp[1])));
				free(tmp);
			}
		}
		else if (cmd[i][0] == '~')
		{
			tmp = get_env(env, "HOME");
			free(cmd[i]);
			cmd[i] = ft_strdup(tmp);
			free(tmp);
		}
	return (1);
}

static void sig_hdlr(int sig)
{
	(void)sig;
}

int		main(int ac, char **av, char **ep)
{
	char	*line;
	char	**env;
	int		i;
	char	**parse;
	char	**cmd;
	char	prompt[4097];
	char	nani[5];

	i = 0;
	(void)ac;
	(void)av;
	i = 0;
	env = collect_env(ep);
	line = NULL;
	signal(SIGINT, &sig_hdlr);
	while (1)
	{
		ft_putstr(RESET);
		ft_putend_cl(ft_strrchr(getcwd(prompt, 4097), '/') + 1, RED,  " $> ", BLUE);
		ft_putstr(WHITE);
		line = get_line(0);
		parse = NULL;
		if (line)
			parse = ft_strsplit(line, ';');
		i = -1;
		while (parse && parse[++i])
		{
			cmd = ft_strsplit_ws(parse[i]);
			if (!(get_var(env, cmd)))
				continue ;
			deal_cmd(cmd, &env);
			free_tab(&cmd);
		}
		if (parse)
			free_tab(&parse);
		if (line)
			free(line);
	}
	return (0);
}
