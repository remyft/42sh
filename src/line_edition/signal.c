/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 04:50:33 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/29 15:19:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_tools.h"
#include "shell.h"

void	sig_hdlr(int sig)
{
	(void)sig;
}

void	sig_winch(int sig)
{
	t_line *line;

	(void)sig;
	line = get_struct();
	tgetent(NULL, line->term);
	line->nb_col = tgetnum("co");
	line->key = WINCH;
	if (*line->e_cmpl & COMPLETION)
	{
		if (line->is_putb < 2)
			*line->e_cmpl &= ~COMPLETION;
		get_complet(line);
	}
}
