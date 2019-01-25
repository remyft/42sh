/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:37:00 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 12:59:50 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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
