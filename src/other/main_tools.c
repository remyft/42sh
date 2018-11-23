/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 04:42:50 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/23 07:12:18 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "main_tools.h"

t_line	*init_line(char **env)
{
	t_line	*line;
	char	prompt[4097];

	line = ft_memalloc(sizeof(t_line));
	line->e_cmpl = ft_memalloc(sizeof(t_st));
	line->path = get_env(env, "PATH");
	line->term = get_env(env, "TERM");
	tgetent(NULL, line->term);
	line->curr = NULL;
	create_hist(&(line->curr), env);
	if (line->curr)
		line->curr = line->curr->begin;
	define_new_term(&(line->save));
	signal(SIGINT, &sig_hdlr);
	signal(SIGQUIT, &sig_hdlr);
	signal(SIGWINCH, &sig_winch);
	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	ft_bzero(line->buff_tmp, 8194);
	line->tree[0] = create_bin_tree(env);
	line->tree[1] = create_file_tree(".");
	line->tree[2] = NULL;
	line->prompt = ft_strdup(ft_strrchr(getcwd(prompt, 4097), '/') + 1);
	line->lprompt = ft_strlen(line->prompt) + 4;
	line->nb_col = tgetnum("co");
	line->slct_beg = -1;
	line->slct_end = -1;
	return (line);
}

void	deal_key(t_line *line)
{
	int				i;
	static t_fctn	fctn[] = {
		{ "\x2" , &prev_word },
		{ "\x3" , &deal_cancel },
		{ "\x4" , &deal_exit },
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
		{ "\x1B\x5B\x33\x7E" , &del_right },
		{ "\x1B\x5B\x31\x3B\x32\x44", &select_left},
		{ "\x1B\x5B\x31\x3B\x32\x43", &select_right} };

	/*i = -1;
	while (line->tmp[++i])
		ft_putnbend(line->tmp[i], "  \n");
*/	i = -1;
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
		line->path = ft_strdup(path);
		free(path);
	}
}

void	deal_typing(t_line *line)
{
	int		nb_read;

	nb_read = 0;
	line->len = 0;
	line->index = 0;
	ft_bzero(line->tmp, 10);
	while ((line->tmp[0] != 10 && line->tmp[0] != -1) || *(line->e_cmpl) & COMPLETION)
	{
		ft_bzero(line->tmp, 10);
		if (line->len + (nb_read = read(0, line->tmp, 10)) < 8192) /* Type and cmd+V */
			line->len = get_typing(&(line->index), line->buff, line->tmp, nb_read, line->buff_tmp);
		if (is_change)
			deal_winch(line);
		line->tmp[nb_read] = '\0';
		if (line->tmp[0] == '/')
			line->tree[2] = free_tree(line->tree[2]);
		else if (line->tmp[0] != 9)
			deal_reset(line->tree[0], line->tree[1], NULL);
		deal_key(line);
		if (*(line->e_cmpl) & COMPLETION && line->tmp[0] == 10)
			set_complet(line);
	}
}