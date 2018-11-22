/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:54:35 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/22 05:13:12 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	next_word(t_line *line)
{
	int		lenp;

	lenp = ft_strlen(line->prompt) + 3;
	while (line->buff[line->index] != ' ' && line->index < line->len)
	{
		if (line->len > line->nb_col)
			if ((line->index + lenp) % line->nb_col == 0 && line->index < line->len)
				tputs(tgetstr("do", NULL), 1, ft_pchar);
		line->index = line->index + 1;
	}
	while (line->index < line->len && line->buff[line->index] == ' ')
		line->index = line->index + 1;
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->index + lenp) % line->nb_col), 1, ft_pchar);
}

void	prev_word(t_line *line)
{
	int		lenp;

	lenp = ft_strlen(line->prompt) + 3;
	if (line->index == line->len && line->len != 0)
		line->index = line->index - 1;
	if (ft_isprint(line->buff[line->index]) && line->buff[line->index] != ' ' && line->index > 0)
		line->index = line->index - 1;
	while (line->buff[line->index] == ' ')
		line->index = line->index - 1;
	while (line->buff[line->index] != ' ' && line->index > 0)
	{
		if (line->len > line->nb_col)
			if ((line->index + lenp) % line->nb_col == 0 && line->index > 0)
				tputs(tgetstr("up", NULL), 1, ft_pchar);
		line->index = line->index - 1;
	}
	while (line->index > 0 && line->buff[line->index] == ' ')
		line->index = line->index + 1;
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->index + lenp) % line->nb_col), 1, ft_pchar);
}

