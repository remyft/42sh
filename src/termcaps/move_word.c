/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:54:35 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 03:45:55 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	next_word(t_line *line)
{
	int		lenp;

	lenp = line->lprompt;
	while (line->curr->buff[line->index] != ' ' && line->index < line->len)
	{
		if (line->len > line->nb_col)
			if ((line->index + lenp) % line->nb_col == 0
				&& line->index < line->len)
				tputs(tgetstr("do", NULL), 1, ft_pchar);
		line->index = line->index + 1;
	}
	while (line->index < line->len && line->curr->buff[line->index] == ' ')
		line->index = line->index + 1;
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->index + lenp) % line->nb_col), 1, ft_pchar);
}

void	prev_word(t_line *line)
{
	if (line->index == line->len && line->len != 0)
		line->index = line->index - 1;
	else if (ft_isprint(line->curr->buff[line->index])
			&& line->curr->buff[line->index] != ' ' && line->index > 0)
		line->index = line->index - 1;
	while (line->curr->buff[line->index] == ' ')
		line->index = line->index - 1;
	while (line->curr->buff[line->index] != ' ' && line->index > 0)
	{
		if (line->len > line->nb_col)
			if ((line->index + line->lprompt) % line->nb_col == 0
					&& line->index > 0)
				tputs(tgetstr("up", NULL), 1, ft_pchar);
		line->index = line->index - 1;
	}
	while (line->index > 0 && line->curr->buff[line->index] == ' ')
		line->index = line->index + 1;
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->index + line->lprompt) % line->nb_col), 1, ft_pchar);
}
