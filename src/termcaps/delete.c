/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:51:36 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/22 04:53:20 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_lines(t_line *line)
{
	int		i;
	int		j;
	char	prompt[4097];
	int		lenp;
	char	*term;
	int		nb_col;

	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	lenp = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	i = (line->index + lenp) / nb_col - 1;
	j = (line->len + lenp) / nb_col;
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	while (++i < j)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
		tputs(tgetstr("dl", NULL), 1, ft_pchar);
	}
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
}

static void	del_left(t_line *line)
{
	int		j;
	char	*term;
	int		len;
	int		nb_col;
	char	prompt[4097];

	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	j = 0;
	len = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	line->len = ft_strlen(line->buff);
	if (line->index && (line->index + len) % nb_col == 0)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	if (line->index != 0)
	{
		line->index = line->index > 0 ? line->index - 1 : 0;
		while (line->index + j < line->len)
		{
			line->buff[line->index + j] = line->buff[line->index + j + 1];
			j++;
		}
		line->buff[line->len] = '\0';
		line->len = line->len > 0 ? line->len - 1 : 0;
		tputs(tgoto(tgetstr("ch", NULL), 0, (line->index + len) % nb_col), 1, ft_pchar);
		tputs(tgetstr("dc", NULL), 1, ft_pchar);
	}
	if ((line->index + len) % nb_col == nb_col - 1)
	{
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		ft_putchar(' ');
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
	}
	if (line->len + len > nb_col - 1)
	{
		del_lines(line);
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		line->index < line->len ? ft_putstr(&(line->buff[line->index])) : ft_putstr("");
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
	}
	if (line->curr && ft_strcmp(line->curr->content, line->buff) != 0)
		ft_strcpy(line->buff_tmp, line->buff);
}

void	deal_dleft(t_line *line)
{
	if (*(line->e_cmpl) & COMPLETION)
	{
		delete_down();
		*(line->e_cmpl) &= ~COMPLETION;
		ft_bzero(line->buff_tmp, 8194);
	}
	else
		del_left(line);
}

void	del_right(t_line *line)
{
	int		j;
	char	*term;
	int		nb_col;

	if (*(line->e_cmpl) & COMPLETION)
		line->tmp[0] = 10;
	else
	{
		term = getenv("TERM");
		tgetent(NULL, term);
		nb_col = tgetnum("co");
		j = -1;
		while (line->index + ++j < line->len)
			line->buff[line->index + j] = line->buff[line->index + j + 1];
		tputs(tgetstr("dc", NULL), 1, ft_pchar);
		del_lines(line);
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		line->index < line->len ? ft_putstr(&(line->buff)[line->index]) : ft_putstr("");
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
		line->len = line->len > line->index ? line->len - 1 : line->index;
	}
}

