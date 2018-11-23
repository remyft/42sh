/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:46:41 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/23 02:50:11 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	deal_exit(t_line *line)
{
	t_hist *curr;

	if (line->buff[0])
	{
		ft_putendl("GNE");
		return ;
	}
	term_restore(line->save);
	if (line->tree[0])
		free_tree(line->tree[0]);
	if (line->tree[1])
		free_tree(line->tree[1]);
	if (line->tree[2])
		free_tree(line->tree[2]);
	ft_putchar('\n');
	while (line->curr)
	{
		curr = line->curr->next;
		if (line->curr->content)
			free(line->curr->content);
		if (line->curr->tmp)
			free(line->curr->tmp);
		free(line->curr);
		line->curr = curr;
	}
	exit(0);
}

static int		ft_cancel(t_line *line)
{
	line->len = line->len % line->nb_col < line->nb_col ? line->len
		+ (line->nb_col - line->len % line->nb_col) : line->len;
	while ((line->index = line->index + line->nb_col) < line->len)
		ft_putchar('\n');
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	ft_bzero(line->buff_tmp, 8194);
	if (!line->curr)
		return (-1);
	line->curr = line->curr->begin;
	while (line->curr->next)
	{
		if (line->curr->tmp)
			free(line->curr->tmp);
		line->curr->tmp = NULL;
		line->curr = line->curr->next;
	}
	if (line->curr->tmp)
		free(line->curr->tmp);
	line->curr->tmp = NULL;
	line->curr = line->curr->begin;
	return (-1);
}

void	deal_cancel(t_line *line)
{
	if (*(line->e_cmpl) & COMPLETION)
	{
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
		tputs(tgetstr("cd", NULL), 1, ft_pchar);
		put_prompt(line->prompt);
		ft_bzero(line->buff, line->len);
		ft_strcpy(line->buff, line->buff_tmp);
		ft_bzero(line->buff_tmp, 8194);
		ft_putstr(line->buff);
		line->index = ft_strlen(line->buff);
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
			free_tree(line->tree[2]);
		line->tree[2] = NULL;
		line->tmp[0] = ft_cancel(line);
	}
	*(line->e_cmpl) &= ~COMPLETION;
}

void	ft_clear(t_line *line)
{
	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	put_prompt(line->prompt);
	ft_putstr(line->buff);
}
