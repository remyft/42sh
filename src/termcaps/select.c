/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 05:18:39 by rfontain          #+#    #+#             */
/*   Updated: 2018/12/12 17:03:14 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putselect(t_line *line)
{
	size_t	i;

	i = line->index / line->nb_col;
	while (i--)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	put_prompt(line->prompt);
	i = -1;
	while (++i < (size_t)line->slct_beg)
		ft_putchar(line->curr->buff[i]);
	tputs(tgetstr("mr", NULL), 1, ft_pchar);
	while (i < (size_t)line->slct_end)
		ft_putchar(line->curr->buff[i++]);
	tputs(tgetstr("me", NULL), 1, ft_pchar);
	while (i < line->len)
		ft_putchar(line->curr->buff[i++]);
	i = ((line->len + (line->len % line->nb_col)) - line->index) / line->nb_col;
	while (i--)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->lprompt + line->index) % line->nb_col), 1, ft_pchar);
}

void	select_left(t_line *line)
{
	if (line->slct_beg < 0)
	{
		line->slct_end = (int)line->index;
		line->slct_beg = line->slct_end > 0 ? line->slct_end - 1 : 0;
		line->index = (size_t)line->slct_beg;
	}
	else
	{
		if (line->slct_beg == (int)line->index)
		{
			line->slct_beg = line->slct_beg > 0 ? line->slct_beg - 1 : 0;
			line->index = (size_t)line->slct_beg;
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
	if (line->slct_beg < 0)
	{
		line->slct_beg = (int)line->index;
		line->slct_end = line->slct_beg < (int)line->len ? line->slct_beg + 1 : line->len;
		line->index = (size_t)line->slct_end;
	}
	else
	{
		if (line->slct_end == (int)line->index)
		{
			line->slct_end = line->slct_end < (int)line->len ? line->slct_end + 1 : line->len;
			line->index = (size_t)line->slct_end;
		}
		else
		{
			line->slct_beg += 1;
			line->index += 1;
		}
	}
	ft_putselect(line);
}

void	ft_copy(t_line *line)
{
	if (line->slct_beg < 0)
		return ;
	if (line->copy)
		free(line->copy);
	line->copy = ft_strndup(&(line->curr->buff[line->slct_beg]), line->slct_end - line->slct_beg);
}

void	ft_cut(t_line *line)
{
	int beg;
	int end;

	if (line->slct_beg < 0)
		return ;
	ft_copy(line);
	beg = line->slct_beg;
	end = line->slct_end;
	while (line->curr->buff[beg])
	{
		if (line->curr->buff[end])
			line->curr->buff[beg] = line->curr->buff[end++];
		else
			line->curr->buff[beg] = '\0';
		beg++;
	}
	line->len = ft_strlen(line->curr->buff);
	tputs(tgoto(tgetstr("ch", NULL), 0, line->lprompt), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	ft_putstr(line->curr->buff);
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->lprompt + line->index) % line->nb_col), 1, ft_pchar);

}

void	ft_paste(t_line *line)
{
	char	c;
	char	d;
	size_t	i;
	int		j;

	if (!line->copy)
		return ;
	i = 0;
	j = 0;
	while (line->copy[j])
	{
		if (line->index > 8192)
			break ;
		d = line->curr->buff[line->index + 1];
		line->curr->buff[line->index + 1] = line->curr->buff[line->index];
		line->curr->buff[line->index] = line->copy[j];
		i = line->index + 1;
		while (line->curr->buff[i])
		{
			c = line->curr->buff[i + 1];
			line->curr->buff[i + 1] = d;
			d = c;
			i++;
		}
		j++;
		line->index++;
	}
	line->len = ft_strlen(line->curr->buff);
	i = line->index / line->nb_col;
	while (i--)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, line->lprompt), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	ft_putstr(line->curr->buff);
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->lprompt + line->index) % line->nb_col), 1, ft_pchar);
}
