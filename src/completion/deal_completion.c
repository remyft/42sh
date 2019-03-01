/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:38:48 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/28 01:41:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "put.h"
#include "shell_lib.h"
#include "shell_term.h"

static void	put_cpl_screen(t_line *line, int nb_ret)
{
	line->len = ft_strlen(line->curr->buff);
	line->index = line->len;
	while (nb_ret-- + 1)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_pchar);
	put_prompt(line->prompt);
	ft_putstr(line->curr->buff);
	if ((line->len + line->lprompt) % line->nb_col == 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
	}
}

int			deal_ret(t_tree *file, t_line *line, int *nb_ret, int put)
{
	if ((put = put_complet(file, &put, line, nb_ret)) == 1)
	{
		*line->e_cmpl |= COMPLETION;
		line->tmp[0] = 10;
	}
	else if (put == -1)
	{
		line->is_putb = 0;
		line->tmp[0] = 0;
		tputs(tgetstr("up", NULL), 1, ft_pchar);
		if (line->lprompt + line->len >= line->nb_col)
			tputs(tgetstr("up", NULL), 1, ft_pchar);
		put_prompt(line->prompt);
		ft_putstr(line->curr->buff);
		if ((line->len + line->lprompt) % line->nb_col == 0)
		{
			tputs(tgetstr("do", NULL), 1, ft_pchar);
			tputs(tgetstr("cr", NULL), 1, ft_pchar);
		}
		return (1);
	}
	return (0);
}

void		deal_complet(t_tree *file, t_line *line)
{
	int		nb_ret;

	nb_ret = 0;
	go_home(line);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	go_end(line);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_pchar);
	if (!line->curr->buff_tmp[8193])
	{
		ft_strcpy(line->curr->buff_tmp, line->curr->buff);
		line->curr->buff_tmp[8193] = 1;
		if (deal_ret(file, line, &nb_ret, 0))
			return ;
	}
	else
	{
		if (deal_ret(file, line, &nb_ret, 1))
			return ;
	}
	if ((ft_strlen(line->curr->buff_tmp) + line->lprompt) >= line->nb_col)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	if ((line->len + line->lprompt) % line->nb_col <
			(ft_strlen(line->curr->buff_tmp) + line->lprompt) % line->nb_col)
	{
		if (line->is_putb >= 1)
			tputs(tgetstr("up", NULL), 1, ft_pchar);
	}
	put_cpl_screen(line, nb_ret);
}
