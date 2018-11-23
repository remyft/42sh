/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:13:27 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/22 18:19:30 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_home(t_line *line)
{
	int		i;
	int		len;

	len = ft_strlen(line->prompt) + 4;
	i = (len + line->index) / line->nb_col;
	while (i--)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, len), 1, ft_pchar);
	line->index = 0;
}

void	go_end(t_line *line)
{
	int		i;
	int		j;
	int		lenp;

	lenp = ft_strlen(line->prompt) + 4;
	i = (line->index + lenp) / line->nb_col - 1;
	j = (line->len + lenp) / line->nb_col;
	while (++i < j)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->len + lenp) % line->nb_col), 1, ft_pchar);
	line->index = line->len;
}

void	left_arrow(t_line *line)
{
	int		len;

	len = ft_strlen(line->prompt) + 4;
	line->index = line->index > 0 ? line->index - 1 : 0;
	if (line->index && (line->index + len) % line->nb_col == line->nb_col - 1)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->index + len) % line->nb_col), 1, ft_pchar);
}

void	right_arrow(t_line *line)
{
	int		len;

	len = ft_strlen(line->prompt) + 4;
	line->index = line->index < line->len ? line->index + 1 : line->len;
	if (line->index && (line->index + len) % line->nb_col == 0)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->index + len) % line->nb_col), 1, ft_pchar);
}
