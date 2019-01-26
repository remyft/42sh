/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:46:41 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 15:43:36 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void			deal_exit(t_line *line)
{
	int		i;
	t_hist	*curr;

	if (line->curr->buff[0])
		return ;
	term_restore(line->save);
	free_all_tree(line);
	ft_putchar('\n');
	while (line->hist)
	{
		curr = line->hist->next;
		if (line->hist->content)
			free(line->hist->content);
		if (line->hist->tmp)
			free(line->hist->tmp);
		free(line->hist);
		line->hist = curr;
	}
	i = -1;
	while (++i < NSIG)
		signal(i, SIG_DFL);
	exit(0);
}

static int		ft_cancel(t_line *line)
{
	while ((line->index = line->index + line->nb_col) < line->len)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->len + line->lprompt) % line->nb_col), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	ft_bzero(line->curr->buff_tmp, 8194);
	del_all_state(line);
	free_hdoc(line);
	reset_hist(line);
	reset_buff(line);
	line->len = 0;
	line->index = 0;
	return (-1);
}

void			deal_cancel(t_line *line)
{
	if (*(line->e_cmpl) & COMPLETION)
	{
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
		tputs(tgetstr("cd", NULL), 1, ft_pchar);
		put_prompt(line->prompt);
		ft_bzero(line->curr->buff, line->len);
		ft_strcpy(line->curr->buff, line->curr->buff_tmp);
		ft_bzero(line->curr->buff_tmp, 8194);
		ft_putstr(line->curr->buff);
		line->index = ft_strlen(line->curr->buff);
		line->len = line->index;
		reset_put(line->tree[0]);
		reset_put(line->tree[1]);
		if (line->tree[2])
			reset_put(line->tree[2]);
		line->tmp[0] = 3;
	}
	else
	{
		if (line->tree[2])
			line->tree[2] = free_tree(line->tree[2]);
		line->tmp[0] = ft_cancel(line);
	}
	*(line->e_cmpl) &= ~COMPLETION;
	line->is_putb = 0;
}

void			ft_clear(t_line *line)
{
	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	put_prompt(line->prompt);
	ft_putstr(line->curr->buff);
}
