/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:46:41 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/22 21:04:05 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	deal_exit(t_line *line)
{
	t_hist *curr;

	if (line->buff[0])
		return ;
	term_restore(line->save);
	if (line->tree[0])
		free_tree(line->tree[0]);
	if (line->tree[1])
		free_tree(line->tree[1]);
	if (line->tree[2])
		free_tree(line->tree[2]);
	ft_putchar('\n');
	if (line->curr)
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

static int		ft_cancel(int index, int i, char *buff_tmp, t_hist **curr)
{
	char	*term;
	int		nb_col;

	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	i = i % nb_col < nb_col ? i + (nb_col - i % nb_col) : i;
	while ((index = index + nb_col) < i)
		ft_putchar('\n');
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	*curr = (*curr)->begin;
	ft_bzero(buff_tmp, 8194);
	while ((*curr)->next)
	{
		if ((*curr)->tmp)
			free((*curr)->tmp);
		(*curr)->tmp = NULL;
		(*curr) = (*curr)->next;
	}
	if ((*curr)->tmp)
		free((*curr)->tmp);
	(*curr)->tmp = NULL;
	*curr = (*curr)->begin;
	ft_putendl("");
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
		line->tmp[0] = ft_cancel(line->index, line->len, line->buff_tmp, &(line->curr));
	}
	*(line->e_cmpl) &= ~COMPLETION;
}

void	ft_clear(t_line *line)
{
	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	put_prompt(line->prompt);
	ft_putstr(line->buff);
}
