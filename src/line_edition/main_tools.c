/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 04:42:50 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/11 16:17:52 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "shell.h"
#include "shell_lib.h"
#include "main_tools.h"
#include "put.h"
#include "history.h"

void	set_signal(void)
{
	signal(SIGINT, &sig_hdlr);
	signal(SIGQUIT, &sig_hdlr);
	signal(SIGWINCH, &sig_winch);
}

void	create_all_tree(t_line *line)
{
	free_all_tree(line);
	if (sh_getnenv("PATH", *line->public_env))
		GET_TREE(line->tree, BIN) = create_bin_tree(*line->public_env);
	else if (sh_getnenv("PATH", *line->private_env))
		GET_TREE(line->tree, BIN) = create_bin_tree(*line->private_env);
	GET_TREE(line->tree, FILES) = create_file_tree(".", NULL, NULL);
	GET_TREE(line->tree, TMP) = NULL;
	fill_tree_env(*line->public_env, &GET_TREE(line->tree, ENV));
	fill_tree_env(*line->private_env, &GET_TREE(line->tree, ENV));
	if (GET_TREE(line->tree, ENV))
		set_psblty(GET_TREE(line->tree, ENV));
}

void	init_line(char **env, t_line *line)
{
	line->e_cmpl = ft_memalloc(sizeof(t_st));
	line->path = get_env(env, "PATH");
	line->term = get_env(env, "TERM");
	tgetent(NULL, line->term);
	create_hist(&(line->hist), env);
	if (line->hist)
		line->hist = line->hist->begin;
	tcgetattr(0, &line->save);
	set_signal();
	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	create_all_tree(line);
	line->prompt = ft_strdup("$> ");
	line->lprompt = ft_strlen(line->prompt);
	line->nb_col = tgetnum("co");
	line->nb_line = tgetnum("li");
	line->slct_beg = -1;
	line->slct_end = -1;
	line->shell_loop = 1;
}

void	deal_key(t_line *line)
{
	int				i;
	static t_fctn	fctn[] = {
		{ "\x3", &deal_cancel }, { "\x4", &deal_exit },
		{ "\x9", &get_complet }, { "\xB", &ft_clear },
		{ "\x7F", &deal_dleft }, { "\x1B\x5B\x41", &up_arrow },
		{ "\x1B\x5B\x42", &down_arrow }, { "\x1B\x5B\x43", &right_arrow },
		{ "\x1B\x5B\x44", &left_arrow }, { "\x1B\x5B\x46", &go_end },
		{ "\x1B\x5B\x48", &deal_home }, { "\x1B\x5B\x33\x7E", &del_right },
		{ "\x1B\x5B\x31\x3B\x32\x44", &select_left},
		{ "\x1B\x5B\x31\x3B\x32\x43", &select_right},
		{ "\x17", &next_word }, { "\x2", &prev_word },
		{ "\xC3\xA7", &ft_copy }, { "\xE2\x88\x9A", &ft_paste },
		{ "\xE2\x89\x88", &ft_cut }, { "\x1B\x1B\x5B\x41", &mv_line_up},
		{ "\x1B\x1B\x5B\x42", &mv_line_down},
		{ "\x1B\x5B\x31\x3B\x32\x41", &select_up},
		{ "\x1B\x5B\x31\x3B\x32\x42", &select_down} };

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
	if (path && line->path && ft_strcmp(path, line->path) != 0)
	{
		free_tree(line->tree[0]);
		line->tree[0] = create_bin_tree(env);
		free(line->path);
		line->path = path;
	}
	else
		free(path);
}
