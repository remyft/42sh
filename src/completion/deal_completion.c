/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:38:48 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/07 03:44:13 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "put.h"
#include "shell_lib.h"

static void	put_cpl_screen(t_line *line, int nb_ret)
{
	size_t	j;

	while (nb_ret-- + 1)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, ft_strlen(line->prompt)), 1, ft_pchar);
	j = 0;
	while (j < line->len)
	{
		tputs(tgetstr("dc", NULL), 1, ft_pchar);
		j++;
	}
	ft_putstr(line->curr->buff);
	line->len = ft_strlen(line->curr->buff);
	line->index = line->len;
}

void		deal_complet(t_tree *file, t_line *line)
{
	int		put;
	int		nb_ret;

	put = 0;
	nb_ret = 0;
	if (!line->curr->buff_tmp[8193])
	{
		ft_strcpy(line->curr->buff_tmp, line->curr->buff);
		line->curr->buff_tmp[8193] = 1;
	}
	else
		put = 1;
	if ((put = put_complet(file, &put, line, &nb_ret)) == 1)
	{
		*line->e_cmpl |= COMPLETION;
		line->tmp[0] = 10;
	}
	else if (put == -1)
	{
		line->is_putb = 0;
		line->tmp[0] = 0;
		return ;
	}
	put_cpl_screen(line, nb_ret);
}
