/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 05:59:37 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/07 06:53:32 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_term.h"

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
	int		len;

	if (!line->copy)
		return ;
	j = 0;
	index_tmp = line->index;
	if (line->len + (len = ft_strlen(line->copy)) > 8192)
		return ;
	while (line->copy[j])
		if (get_paste(line, &j))
			break ;
	line->len += len;
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	ft_putstr(&line->curr->buff[index_tmp]);
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
	j = line->index;
	line->index = index_tmp;
	while (line->index < (size_t)j)
		right_arrow(line);
}
