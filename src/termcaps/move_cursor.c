/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:13:27 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/23 18:07:02 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_term.h"
#include "put.h"
#include "struct.h"

void	go_home(t_line *line)
{
	int		i;

	i = (line->lprompt + line->index) / line->nb_col;
	while (i--)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, line->lprompt), 1, ft_pchar);
	line->index = 0;
}

void	deal_home(t_line *line)
{
	if (*line->e_cmpl & COMPLETION)
	{
		go_end(line);
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
		tputs(tgetstr("cd", NULL), 1, ft_pchar);
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
		*line->e_cmpl &= ~COMPLETION;
	}
	go_home(line);
}

void	go_end(t_line *line)
{
	int		i;
	int		j;

	i = (line->index + line->lprompt) / line->nb_col - 1;
	j = (line->len + line->lprompt) / line->nb_col;
	while (++i < j)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->len + line->lprompt) % line->nb_col), 1, ft_pchar);
	line->index = line->len;
}

void	left_arrow(t_line *line)
{
	if (*line->e_cmpl & COMPLETION && line->is_putb)
	{
		line->key = LEFT;
		get_complet(line);
		return ;
	}
	if (line->curr->buff_tmp[MAX_SHELL_LEN + 1])
	{
		ft_bzero(line->curr->buff_tmp, MAX_SHELL_LEN + 2);
		while (line->hist->prev)
			line->hist = line->hist->prev;
	}
	if (line->index > 0)
		line->index -= 1;
	else
		write(2, "\a", 1);
	if (line->index
			&& (line->index + line->lprompt) % line->nb_col == line->nb_col - 1)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->index + line->lprompt) % line->nb_col), 1, ft_pchar);
}

void	right_arrow(t_line *line)
{
	if (*line->e_cmpl & COMPLETION && line->is_putb)
	{
		line->key = RIGHT;
		get_complet(line);
		return ;
	}
	if (line->curr->buff_tmp[MAX_SHELL_LEN + 1])
	{
		ft_bzero(line->curr->buff_tmp, MAX_SHELL_LEN + 2);
		while (line->hist->prev)
			line->hist = line->hist->prev;
	}
	if (line->index == line->len)
	{
		ft_putchar_fd('\a', 2);
		return ;
	}
	line->index += 1;
	if (line->index && (line->index + line->lprompt) % line->nb_col == 0)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->index + line->lprompt) % line->nb_col), 1, ft_pchar);
}
