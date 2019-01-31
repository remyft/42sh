/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:46:41 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/31 20:16:17 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "shell.h"

#ifdef __linux__
# define NSIG _NSIG
#endif

void			free_hist(t_hist *hist)
{
	if (!hist)
		return ;
	if (hist)
		free_hist(hist->next);
	if (hist->tmp)
		free(hist->tmp);
	free(hist->content);
	free(hist);
}

void			free_struct(t_line *line)
{
	free_all_tree(line);
	free_buff(line);
	free_hist(line->hist);
	free(line->e_cmpl);
	free(line->prompt);
	if (line->copy)
		free(line->copy);
	if (line->path)
		free(line->path);
	if (line->term)
		free(line->term);
	free(line);
}

void			deal_exit(t_line *line)
{
	int		i;

	if (line->curr->prev || line->curr->buff[0])
		return ;
	term_restore(line->save);
	i = -1;
	while (++i < NSIG)
		signal(i, SIG_DFL);
	line->shell_loop = 0;
}

static int		ft_cancel(t_line *line)
{
	while ((line->index = line->index + line->nb_col) < line->len)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->len + line->lprompt) % line->nb_col), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	init_new_buff(line);
	del_all_state(line);
	free_hdoc(line);
	reset_hist(line);
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
		ft_bzero(line->curr->buff_tmp, ft_strlen(line->curr->buff_tmp));
		line->curr->buff_tmp[8193] = 0;
		ft_putstr(line->curr->buff);
		line->index = ft_strlen(line->curr->buff);
		line->len = line->index;
		deal_reset(line->tree[0], line->tree[1], line->tree[2]);
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
