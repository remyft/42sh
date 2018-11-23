/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 05:18:39 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/23 07:16:36 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putselect(t_line *line)
{
	int i;

	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	put_prompt(line->prompt);
	i = -1;
	while (++i < line->slct_beg)
		ft_putchar(line->buff[i]);
	tputs(tgetstr("mr", NULL), 1, ft_pchar);
	while (i < line->slct_end)
		ft_putchar(line->buff[i++]);
	tputs(tgetstr("me", NULL), 1, ft_pchar);
	while (i < line->len)
		ft_putchar(line->buff[i++]);
}

void	select_left(t_line *line)
{
	if (line->slct_beg < 0)
	{
		line->slct_end = line->index;
		line->slct_beg = line->slct_end > 0 ? line->slct_end - 1 : 0;
		line->index = line->slct_beg;
	}
	else
	{
		if (line->slct_beg == line->index)
		{
			line->slct_beg = line->slct_beg > 0 ? line->slct_beg - 1 : 0;
			line->index = line->slct_beg;
		}
		else
		{
			line->slct_end -= 1;
			line->index -= 1;
		}
	}
	ft_putselect(line);
}

void	select_right(t_line *line)
{
	(void)line;
/*	if (line->iselect)
		line->iselect = line->iselect < line->len ? line->iselect + 1 : line->len;
	else
		line->iselect = line->index < line->len ? line->index + 1 : line->len;
	ft_putselect(line);*/
}
