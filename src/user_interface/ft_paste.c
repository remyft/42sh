/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 05:59:37 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 13:00:15 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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