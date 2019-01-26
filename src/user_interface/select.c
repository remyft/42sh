/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 05:18:39 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 12:59:57 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	expand_select_left(t_line *line, int diff, int mal)
{
	line->slct_beg = diff > 0 ? diff - mal : 0;
	line->index = (size_t)line->slct_beg;
	tputs(tgetstr("mr", NULL), 1, ft_pchar);
	ft_putchar(line->curr->buff[line->index + 1]);
	tputs(tgetstr("me", NULL), 1, ft_pchar);
	if (line->index
			&& (line->index + line->lprompt) % line->nb_col == line->nb_col - 1)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->lprompt + line->index) % line->nb_col), 1, ft_pchar);
}

void		select_left(t_line *line)
{
	if (line->index == 0)
		return ;
	if (line->slct_beg < 0)
	{
		line->slct_end = (int)line->index + 1;
		expand_select_left(line, line->slct_end, 2);
	}
	else
	{
		if (line->slct_beg == (int)line->index)
			expand_select_left(line, line->slct_beg, 1);
		else
		{
			ft_putchar(line->curr->buff[line->index]);
			line->slct_end -= 1;
			line->index -= 1;
			if (line->index
					&& (line->index + line->lprompt) % line->nb_col ==
					line->nb_col - 1)
				tputs(tgetstr("up", NULL), 1, ft_pchar);
			tputs(tgoto(tgetstr("ch", NULL), 0,
						(line->lprompt + line->index) % line->nb_col), 1,
							ft_pchar);
		}
	}
}

static void	expand_select_right(t_line *line, int diff)
{
	line->slct_end = diff < (int)line->len ? diff + 1 : line->len;
	line->index = (size_t)line->slct_end;
	tputs(tgetstr("mr", NULL), 1, ft_pchar);
	ft_putchar(line->curr->buff[line->index - 1]);
	tputs(tgetstr("me", NULL), 1, ft_pchar);
	if (line->index && (line->index + line->lprompt) % line->nb_col == 0)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->lprompt + line->index) % line->nb_col), 1, ft_pchar);
}

void		select_right(t_line *line)
{
	if (line->index == line->len)
		return ;
	if (line->slct_beg < 0)
	{
		line->slct_beg = (int)line->index;
		expand_select_right(line, line->slct_beg);
	}
	else
	{
		if (line->slct_end == (int)line->index)
			expand_select_right(line, line->slct_end);
		else
		{
			ft_putchar(line->curr->buff[line->index]);
			line->slct_beg += 1;
			line->index += 1;
			if (line->index && (line->index + line->lprompt) % line->nb_col ==
					0)
				tputs(tgetstr("do", NULL), 1, ft_pchar);
			tputs(tgoto(tgetstr("ch", NULL), 0,
						(line->lprompt + line->index) % line->nb_col), 1,
							ft_pchar);
		}
	}
}