/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:57:17 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/14 16:16:17 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "shell_term.h"
#include "put.h"
#include "libft.h"

#include "stdio.h"

static void	get_to_len(t_line *line, char tchar)
{
	char	cbis;
	int		j;

	j = 1;
	while (line->index + j < line->len)
	{
		cbis = line->curr->buff[line->index + j];
		line->curr->buff[line->index + j] = tchar;
		tchar = cbis;
		j++;
	}
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	ft_putstr(&(line->curr->buff[line->index]));
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
}

static void	get_to_buff(t_line *line, int *cp)
{
	char	tchar;
	int		j;

	tchar = line->curr->buff[line->index + 1];
	if (line->index != line->len)
		line->curr->buff[line->index + 1] = line->curr->buff[line->index];
	line->curr->buff[line->index++] = line->tmp[*cp];
	line->len++;
	j = 1;
	ft_putchar(line->tmp[*cp]);
	*cp += 1;
	if (line->index != line->len)
		get_to_len(line, tchar);
	if ((line->index + line->lprompt) % line->nb_col == 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
	}
}

void		get_typing(t_line *line, int nb_read)
{
	int		cp;

	cp = 0;
	line->tmp[nb_read] = '\0';
	if (ft_isprint(line->tmp[0]) && *line->e_cmpl & COMPLETION)
	{
		if (line->is_putb == 1)
			set_complet(line, 0);
		else
		{
			line->is_putb -= 1;
			ft_bzero(line->curr->buff_tmp, 8193);
			line->curr->buff_tmp[8193] = 0;
			*line->e_cmpl &= ~COMPLETION;
			line->index = line->len;
		}
	}
	if (line->tmp[0] == 11)
		return ;
	while (cp < nb_read && line->tmp[0] != 12 && (ft_isprint(line->tmp[cp])
				|| ft_isspace(line->tmp[cp]))
			&& line->tmp[0] != 9 && line->tmp[cp] != 10)
		get_to_buff(line, &cp);
}
