/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 04:50:33 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/23 16:53:40 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_tools.h"
#include "put.h"

void		sig_hdlr(int sig)
{
	(void)sig;
}

static void	deal_put_winch(t_line *line)
{
	size_t	index;

	index = line->index;
	go_home(line);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	put_prompt(line->prompt);
	ft_putstr(line->curr->buff);
	line->index = line->len;
	while (line->index != index)
	{
		left_arrow(line);
		line->index--;
	}
	if (*line->e_cmpl & COMPLETION)
	{
		if (line->is_putb < 2)
			*line->e_cmpl &= ~COMPLETION;
		get_complet(line);
	}
}

void		sig_winch(int sig)
{
	t_line *line;

	(void)sig;
	line = get_struct();
	tgetent(NULL, line->term);
	line->nb_col = tgetnum("co");
	line->nb_line = tgetnum("li");
	line->key = WINCH;
	deal_put_winch(line);
}
