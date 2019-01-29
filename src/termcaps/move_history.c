/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 05:00:51 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/29 23:21:46 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			find_hist(t_line *line, int way)
{
	size_t	len;

	len = ft_strlen(line->curr->buff_tmp);
	while (line->hist)
	{
		if (line->hist->c_size > len)
			if (ft_strstr(line->hist->content, line->curr->buff_tmp) ==
					line->hist->content
					&& ft_strcmp(line->curr->buff, line->hist->content) != 0)
				return (1);
		if (!(way == 1 ? line->hist->prev : line->hist->next))
			return (2);
		line->hist = (way == 1 ? line->hist->prev : line->hist->next);
	}
	return (0);
}

int			key_complet(t_line *line, int key)
{
	if (*line->e_cmpl & COMPLETION && line->is_putb)
	{
		line->key = key;
		get_complet(line);
		return (1);
	}
	else if (*line->e_cmpl & COMPLETION)
	{
		line->curr->buff_tmp[0] = 0;
		line->curr->buff_tmp[8193] = 0;
		*line->e_cmpl &= ~COMPLETION;
	}
	return (0);
}

void		up_arrow(t_line *line)
{
	int		find;
	t_hist	*tmp;

	find = 0;
	if (key_complet(line, UP))
		return ;
	if (!line->curr->buff_tmp[8193])
	{
		ft_strcpy(line->curr->buff_tmp, line->curr->buff);
		line->curr->buff_tmp[8193] = 1;
	}
	tmp = line->hist;
	find = find_hist(line, 0);
	if (find == 1)
	{
		ft_strcpy(line->curr->buff, line->hist->content);
		put_new_prompt(line);
	}
	else
		line->hist = tmp;
}

void		down_arrow(t_line *line)
{
	int		find;

	find = 0;
	if (!line->curr->buff_tmp[8193])
		return ;
	if (key_complet(line, DOWN))
		return ;
	find = find_hist(line, 1);
	if (find == 1)
	{
		ft_strcpy(line->curr->buff, line->hist->content);
		put_new_prompt(line);
	}
	else if (find == 2)
	{
		ft_bzero(line->curr->buff, 8192);
		ft_strcpy(line->curr->buff, line->curr->buff_tmp);
		line->curr->buff_tmp[0] = 0;
		line->curr->buff_tmp[8193] = 0;
		put_new_prompt(line);
	}
}
