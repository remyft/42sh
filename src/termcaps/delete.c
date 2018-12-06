/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:51:36 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/23 04:19:19 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_lines(t_line *line)
{
	int		i;
	int		j;

	i = (line->index + line->lprompt) / line->nb_col - 1;
	j = (line->len + line->lprompt) / line->nb_col;
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	while (++i < j)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
		tputs(tgetstr("dl", NULL), 1, ft_pchar);
	}
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
}

static void	del_left(t_line *line)
{
	int		j;

	j = 0;
	line->len = ft_strlen(line->curr->buff);
	if (line->index && (line->index + line->lprompt) % line->nb_col == 0)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	if (line->index != 0)
	{
		line->index = line->index > 0 ? line->index - 1 : 0;
		while (line->index + j < line->len)
		{
			line->curr->buff[line->index + j] = line->curr->buff[line->index + j + 1];
			j++;
		}
		line->curr->buff[line->len] = '\0';
		line->len = line->len > 0 ? line->len - 1 : 0;
		tputs(tgoto(tgetstr("ch", NULL), 0, (line->index + line->lprompt) % line->nb_col), 1, ft_pchar);
		tputs(tgetstr("dc", NULL), 1, ft_pchar);
	}
	if ((line->index + line->lprompt) % line->nb_col == line->nb_col - 1)
	{
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		ft_putchar(' ');
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
	}
	if (line->len + line->lprompt > line->nb_col - 1)
	{
		del_lines(line);
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		line->index < line->len ? ft_putstr(&(line->curr->buff[line->index])) : ft_putstr("");
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
	}
	if (line->hist && ft_strcmp(line->hist->content, line->curr->buff) != 0)
		ft_strcpy(line->curr->buff_tmp, line->curr->buff);
}

void	deal_dleft(t_line *line)
{
	if (*(line->e_cmpl) & COMPLETION)
	{
		delete_down();
		*(line->e_cmpl) &= ~COMPLETION;
		ft_bzero(line->curr->buff_tmp, 8194);
	}
	else
		del_left(line);
}

void	del_right(t_line *line)
{
	int		j;

	if (*(line->e_cmpl) & COMPLETION)
		line->tmp[0] = 10;
	else
	{
		j = -1;
		while (line->index + ++j < line->len)
			line->curr->buff[line->index + j] = line->curr->buff[line->index + j + 1];
		tputs(tgetstr("dc", NULL), 1, ft_pchar);
		del_lines(line);
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		line->index < line->len ? ft_putstr(&(line->curr->buff)[line->index]) : ft_putstr("");
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
		line->len = line->len > line->index ? line->len - 1 : line->index;
	}
}
