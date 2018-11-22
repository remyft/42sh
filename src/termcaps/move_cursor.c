/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:13:27 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/22 04:23:53 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_home(t_line *line)
{
	int		i;
	char	*term;
	int		ret;
	int		nb_col;
	char	prompt[4097];
	int		len;

	len = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	term = getenv("TERM");
	ret = tgetent(NULL, term);
	nb_col = tgetnum("co");
	i = (len + line->index) / nb_col;
	while (i--)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, len), 1, ft_pchar);
	line->index = 0;
}

void	go_end(t_line *line)
{
	char	*term;
	int		nb_col;
	int		i;
	int		j;
	char	prompt[4097];
	int		lenp;

	lenp = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	i = (line->index + lenp) / nb_col - 1;
	j = (line->len + lenp) / nb_col;
	while (++i < j)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->len + lenp) % nb_col), 1, ft_pchar);
	line->index = line->len;
}

void	left_arrow(t_line *line)
{
	char	*term;
	int		nb_col;
	char	prompt[4097];
	int		len;

	len = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	line->index = line->index > 0 ? line->index - 1 : 0;
	if (line->index && (line->index + len) % nb_col == nb_col - 1)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->index + len) % nb_col), 1, ft_pchar);
}

void	right_arrow(t_line *line)
{
	char	*term;
	int		nb_col;
	char	prompt[4097];
	int		len;

	len = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	line->index = line->index < line->len ? line->index + 1 : line->len;
	if (line->index && (line->index + len) % nb_col == 0)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->index + len) % nb_col), 1, ft_pchar);
}
