/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 05:59:37 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 08:45:34 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_copy(t_line *line)
{
	if (line->slct_beg < 0)
		return ;
	if (line->copy)
		free(line->copy);
	line->copy = ft_strndup(&(line->curr->buff[line->slct_beg]),
			line->slct_end - line->slct_beg);
}

void		ft_cut(t_line *line)
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
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->lprompt + line->index) % line->nb_col), 1, ft_pchar);
}

static int	get_paste(t_line *line, int *j)
{
	char	c;
	char	tmp;
	int		i;

	i = 0;
	if (line->index > 8192)
		return (1);
	tmp = line->curr->buff[line->index + 1];
	line->curr->buff[line->index + 1] = line->curr->buff[line->index];
	line->curr->buff[line->index] = line->copy[*j];
	i = line->index + 1;
	while (line->curr->buff[i])
	{
		c = line->curr->buff[i + 1];
		line->curr->buff[i + 1] = tmp;
		tmp = c;
		i++;
	}
	*j += 1;
	line->index++;
	return (0);
}

void		ft_paste(t_line *line)
{
	int		index_tmp;
	int		j;

	if (!line->copy)
		return ;
	j = 0;
	index_tmp = line->index;
	while (line->copy[j])
		if (get_paste(line, &j))
			break ;
	line->len = ft_strlen(line->curr->buff);
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	ft_putstr(&line->curr->buff[index_tmp]);
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
	j = line->index;
	line->index = index_tmp;
	while (line->index < (size_t)j)
		right_arrow(line);
}
