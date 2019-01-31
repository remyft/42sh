/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_typing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 08:55:32 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/31 20:13:45 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "main_tools.h"

static void	deal_unselect(t_line *line)
{
	int		tmp;
	int		i;

	if ((size_t)line->slct_beg == line->index)
	{
		tputs(tgetstr("cd", NULL), 1, ft_pchar);
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		ft_putstr(&line->curr->buff[line->index]);
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, (line->index
						+ line->lprompt) % line->nb_col), 1, ft_pchar);
	}
	else
	{
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		tmp = line->index;
		i = line->slct_end - line->slct_beg + 1;
		while (--i)
			left_arrow(line);
		ft_putstr(&line->curr->buff[line->index]);
		line->index = tmp;
		tputs(tgetstr("cd", NULL), 1, ft_pchar);
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
	}
}

static void	get_read(t_line *line, int *nb_read)
{
	if (line->len + (*nb_read = read(0, line->tmp, 10)) < 8192)
		get_typing(line, *nb_read);
	if (ft_strncmp(line->tmp, "\x1B\x5B\x31\x3B\x32", 5) != 0)
	{
		if (line->slct_beg > -1)
			deal_unselect(line);
		if (ft_strcmp(line->tmp, "\xE2\x89\x88") != 0
				&& ft_strcmp(line->tmp, "\xC3\xA7") != 0)
		{
			line->slct_beg = -1;
			line->slct_end = -1;
		}
	}
}

void		deal_typing(t_line *line)
{
	int		nb_read;

	nb_read = 0;
	ft_bzero(line->tmp, 10);
	while ((line->tmp[0] != 10 && line->tmp[0] != -1)
			|| *(line->e_cmpl) & COMPLETION)
	{
		ft_bzero(line->tmp, 10);
		get_read(line, &nb_read);
		line->tmp[nb_read] = '\0';
		if (line->tmp[0] == '/')
			line->tree[2] = free_tree(line->tree[2]);
		else if (!(*line->e_cmpl & COMPLETION))
			deal_reset(line->tree[0], line->tree[1], NULL);
		if (line->key)
			line->key = 0;
		deal_key(line);
		if (!line->shell_loop)
			break ;
		if (*(line->e_cmpl) & COMPLETION && line->tmp[0] == 10)
			set_complet(line, 1);
	}
	write(1, "\n", 1);
}
