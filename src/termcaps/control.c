/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:46:41 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/08 16:19:12 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "shell.h"
#include "libft.h"
#include "shell_term.h"

#ifdef __linux__
# define NSIG _NSIG
#endif

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
	go_end(line);
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
		line->index = ft_strlen(line->curr->buff_tmp);
		line->len = line->index;
		go_home(line);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
		tputs(tgetstr("cd", NULL), 1, ft_pchar);
		put_prompt(line->prompt);
		ft_bzero(line->curr->buff, 8192);
		ft_strcpy(line->curr->buff, line->curr->buff_tmp);
		ft_bzero(line->curr->buff_tmp, 8193);
		line->curr->buff_tmp[8193] = 0;
		ft_putstr(line->curr->buff);
		deal_reset(line->tree);
		line->tmp[0] = 3;
		line->index = line->len;
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
