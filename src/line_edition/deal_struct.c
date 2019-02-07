/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:44:05 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/03 23:19:44 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"
#include "shell.h"

t_line			*get_struct(void)
{
	static t_line	*line = NULL;

	if (!line)
		line = ft_memalloc(sizeof(t_line));
	return (line);
}

void			free_buff(t_line *line)
{
	t_buff	*tmp;

	while (line->curr->prev)
		line->curr = line->curr->prev;
	while (line->curr)
	{
		tmp = line->curr->next;
		free(line->curr);
		line->curr = tmp;
	}
}

static void		free_hist(t_hist *hist)
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
	while (line->hist->prev)
		line->hist = line->hist->prev;
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