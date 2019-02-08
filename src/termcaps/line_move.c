/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:59:39 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/07 06:43:38 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "shell_term.h"

void	mv_line_up(t_line *line)
{
	if ((int)line->index - (int)line->nb_col >= 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_pchar);
		line->index -= line->nb_col;
		tputs(tgoto(tgetstr("ch", NULL), 0,
					(line->index + line->lprompt) % line->nb_col), 1, ft_pchar);
	}
}

void	mv_line_down(t_line *line)
{
	if (line->index + line->nb_col <= line->len)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		line->index += line->nb_col;
		tputs(tgoto(tgetstr("ch", NULL), 0,
					(line->index + line->lprompt) % line->nb_col), 1, ft_pchar);
	}
}
