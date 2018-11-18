/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:53:59 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/18 03:22:56 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!env)
		return (0);
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

void	put_prompt(void)
{
	char	prompt[4097];

	ft_putstr(RESET);
	ft_putend_cl(ft_strrchr(getcwd(prompt, 4097), '/') + 1, RED,  " $> ", BLUE);
	ft_putstr(WHITE);
}

int		main(__unused int ac, __unused char **av, char **ep)
{
	t_line	*line;
	char	**env;
	int		i;
	char	**parse;
	char	**cmd;
	char	prompt[4097];
	int		nb_read;
	char	*term;
	int		put;
	char	*path;
	char	*save_path;
	DIR		*dir;
	static t_fctn	fctn[] = {
		{ "\x2" , &prev_word },
		{ "\x3" , &deal_cancel },
		{ "\x4" , &ft_exit2 }, 
		{ "\x9" , &get_complet },
		{ "\xC" , &ft_clear },
		{ "\x17" , &next_word },
		{ "\x7F" , &deal_dleft },
		{ "\x1B\x5B\x41" , &up_arrow },
		{ "\x1B\x5B\x42" , &down_arrow },
		{ "\x1B\x5B\x43" , &right_arrow },
		{ "\x1B\x5B\x44" , &left_arrow },
		{ "\x1B\x5B\x46" , &go_end },
		{ "\x1B\x5B\x48" , &go_home },
		{ "\x1B\x5B\x33\x7E" , &del_right } };

	i = 0;
	line = ft_memalloc(sizeof(t_line));
	line->e_cmpl = ft_memalloc(sizeof(t_st));
	env = collect_env(ep);
	save_path = get_env(env, "PATH");
	term = get_env(env, "TERM");
	tgetent(NULL, term);
	line->curr = NULL;
	create_hist(&(line->curr), env);
	if (line->curr)
		line->curr = line->curr->begin;
	define_new_term(&(line->save));
	nb_read = 0;
	signal(SIGINT, &sig_hdlr);
	signal(SIGQUIT, &sig_hdlr);
	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	ft_bzero(line->buff_tmp, 8194);
	line->tree[0] = create_tree(env);
	line->tree[1] = create_file_tree(".");
	line->tree[2] = NULL;
	dir = NULL;
	path = NULL;
	while (1)
	{
		put_prompt();
		ft_bzero(line->buff, 8193);
		path = get_env(env, "PATH");
		if (path && ft_strcmp(path, save_path) != 0)
		{
			free_tree(line->tree[0]);
			line->tree[0] = create_tree(env);
			free(save_path);
			save_path = ft_strdup(path);
		}
		if (path)
			free(path);
		line->len = 0;
		line->index = 0;
		line->tmp[0] = '\0';
		while ((line->tmp[0] != 10 && line->tmp[0] != -1) || *(line->e_cmpl) & COMPLETION)
		{
			put = 0;
			if (line->len + (nb_read = read(0, line->tmp, 10)) < 8192) /* Type and cmd+V */
				line->len = get_typing(&(line->index), line->buff, line->tmp, nb_read, line->buff_tmp);
			line->tmp[nb_read] = '\0';
			if (line->tmp[0] == '/')
				line->tree[2] = free_tree(line->tree[2]);
			else if (line->tmp[0] != 9)
				deal_reset(line->tree[0], line->tree[1], NULL);
			i = -1;
			while (++i < (int)sizeof(*fctn) - 1)
				if (ft_strcmp(line->tmp, fctn[i].key) == 0)
				{
					fctn[i].f(line);
					break ;
				}
			if (*(line->e_cmpl) & COMPLETION && line->tmp[0] == 10)
				line->index = set_complet(&(line->tree[2]), line->e_cmpl, line->tmp, line->buff, &(line->len), line->buff_tmp);
		}
		ft_putchar('\n');
		if (line->buff[0] && line->tmp[0] != -1)
		{
			*(line->e_cmpl) &= ~COMPLETION;
			deal_commande(line->index, line->buff, line->buff_tmp, &(line->curr), env);
			parse = NULL;
			parse = ft_strsplit(line->buff, ';');
			i = -1;
			while (parse && parse[++i])
			{
				cmd = ft_strsplit_ws(parse[i]);
				if (!(get_var(env, cmd)))
					continue ;
				deal_cmd(cmd, &env, &(line->save));
				if (line->tree[1])
					free_tree(line->tree[1]);
				line->tree[1] = create_file_tree(getcwd(prompt, 4097));
				if (line->tree[2])
				{
					free_tree(line->tree[2]);
					line->tree[2] = NULL;
				}
				free_tab(&cmd);
			}
			if (parse)
				free_tab(&parse);
		}
	}
	return (0);
}
