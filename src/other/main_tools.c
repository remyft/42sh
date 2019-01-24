/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 04:42:50 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/24 06:22:23 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include "main_tools.h"

void	init_line(char **env, t_line *line)
{
	line->e_cmpl = ft_memalloc(sizeof(t_st));
	line->path = get_env(env, "PATH");
	line->term = get_env(env, "TERM");
	tgetent(NULL, line->term);
	create_hist(&(line->hist), env);
	if (line->hist)
		line->hist = line->hist->begin;
	define_new_term(&(line->save));
	signal(SIGINT, &sig_hdlr);
	signal(SIGQUIT, &sig_hdlr);
	signal(SIGWINCH, &sig_winch);
	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	line->tree[0] = create_bin_tree(env);
	line->tree[1] = create_file_tree(".", NULL);
	line->tree[2] = NULL;
	line->prompt = ft_strdup("$> ");//ft_strdup(ft_strrchr(getcwd(prompt, 4096), '/') + 1);
	line->lprompt = ft_strlen(line->prompt);
	line->nb_col = tgetnum("co");
	line->nb_line = tgetnum("li");
	line->slct_beg = -1;
	line->slct_end = -1;
	line->env = env;
}

#include <stdio.h>

void	deal_key(t_line *line)
{
	int				i;
	static t_fctn	fctn[] = {
		{ "\x3" , &deal_cancel },
		{ "\x4" , &deal_exit },
		{ "\x9" , &get_complet },
		{ "\xC" , &ft_clear },
		{ "\x7F" , &deal_dleft },
		{ "\x1B\x5B\x41" , &up_arrow },
		{ "\x1B\x5B\x42" , &down_arrow },
		{ "\x1B\x5B\x43" , &right_arrow },
		{ "\x1B\x5B\x44" , &left_arrow },
		{ "\x1B\x5B\x46" , &go_end },
		{ "\x1B\x5B\x48" , &go_home },
		{ "\x1B\x5B\x33\x7E" , &del_right },
		{ "\x1B\x5B\x31\x3B\x32\x44", &select_left},
		{ "\x1B\x5B\x31\x3B\x32\x43", &select_right},
//		{ "\x1B\x5B\x31\x3B\x35\x43" , &next_word },
//		{ "\x1B\x5B\x31\x3B\x35\x44" , &prev_word },
		{ "\x15" , &next_word },
		{ "\x2" , &prev_word },
		{ "\xC3\xA7" , &ft_copy },
		{ "\xE2\x88\x9A" , &ft_paste },
		{ "\xE2\x89\x88" , &ft_cut } };

	i = -1;
	while (++i < (int)(sizeof(fctn) / sizeof(*fctn)))
		if (ft_strcmp(line->tmp, fctn[i].key) == 0)
		{
			fctn[i].f(line);
			return ;
		}
}

void	check_path(t_line *line, char **env)
{
	char	*path;

	path = get_env(env, "PATH");
	if (path && ft_strcmp(path, line->path) != 0)
	{
		free_tree(line->tree[0]);
		line->tree[0] = create_bin_tree(env);
		free(line->path);
		line->path = path;
	}
	else
		free(path);
}

void	deal_typing(t_line *line)
{
	int		nb_read;
	int		i;

	nb_read = 0;
	ft_bzero(line->tmp, 10);
	while ((line->tmp[0] != 10 && line->tmp[0] != -1) || *(line->e_cmpl) & COMPLETION)
	{
		ft_bzero(line->tmp, 10);
		if (line->len + (nb_read = read(0, line->tmp, 10)) < 8192) /* Type and cmd+V */
			get_typing(line, nb_read);
		if (ft_strncmp(line->tmp, "\x1B\x5B\x31\x3B\x32", 5) != 0)
		{
			if (line->slct_beg > -1)
			{
				i = line->index / line->nb_col + 1;
				while (i--)
					tputs(tgetstr("up", NULL), 1, ft_pchar);
				tputs(tgetstr("cr", NULL), 1, ft_pchar);
				tputs(tgetstr("cd", NULL), 1, ft_pchar);
				put_prompt(line->prompt);
				ft_putstr(line->curr->buff);
				tputs(tgoto(tgetstr("ch", NULL), 0, (line->index
								+ line->lprompt) % line->nb_col), 1, ft_pchar);
			}
			if (ft_strcmp(line->tmp, "\xE2\x89\x88") != 0
					&& ft_strcmp(line->tmp, "\xC3\xA7") != 0)
			{
				line->slct_beg = -1;
				line->slct_end = -1;
			}
		}
		if (is_change)
			deal_winch(line);
		line->tmp[nb_read] = '\0';
		if (line->tmp[0] == '/')
			line->tree[2] = free_tree(line->tree[2]);
	//	else if (line->tmp[0] != 9 || line->tmp[2] <= 42 || line->tmp[2] >= 44)
	//		deal_reset(line->tree[0], line->tree[1], NULL);
		if (line->key)
			line->key = 0;
		deal_key(line);
		if (*(line->e_cmpl) & COMPLETION && line->tmp[0] == 10)
			set_complet(line);
	}
}
