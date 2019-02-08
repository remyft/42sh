/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 05:00:51 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/07 06:52:35 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "put.h"

int			find_hist(t_line *line, int way)
{
	size_t	len;

	len = ft_strlen(line->curr->buff_tmp);
	while (line->hist)
	{
		if (line->hist->c_size > len)
			if (ft_strstr(line->hist->content, line->curr->buff_tmp) ==
				line->hist->content && (line->hist->tmp ?
					ft_strcmp(line->curr->buff, line->hist->tmp) :
						ft_strcmp(line->curr->buff, line->hist->content)) != 0)
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

void		is_find(t_line *line)
{
	ft_bzero(line->curr->buff, 8192);
	if (line->hist->tmp)
		ft_strcpy(line->curr->buff, line->hist->tmp);
	else
		ft_strcpy(line->curr->buff, line->hist->content);
	put_new_prompt(line);
}

void		up_arrow(t_line *line)
{
	int		find;
	t_hist	*tmp;

	if (key_complet(line, UP))
		return ;
	if (!line->curr->buff_tmp[8193])
	{
		ft_strcpy(line->curr->buff_tmp, line->curr->buff);
		line->curr->buff_tmp[8193] = 1;
	}
	else
	{
		if (line->hist && ft_strcmp(line->hist->content, line->curr->buff))
		{
			if (line->hist->tmp)
				free(line->hist->tmp);
			line->hist->tmp = ft_strdup(line->curr->buff);
		}
	}
	tmp = line->hist;
	find = find_hist(line, 0);
	if (find == 1)
		is_find(line);
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
	if (line->hist && ft_strcmp(line->hist->content, line->curr->buff))
	{
		if (line->hist->tmp)
			free(line->hist->tmp);
		line->hist->tmp = ft_strdup(line->curr->buff);
	}
	find = find_hist(line, 1);
	if (find == 1)
		is_find(line);
	else if (find == 2)
	{
		ft_bzero(line->curr->buff, 8192);
		ft_strcpy(line->curr->buff, line->curr->buff_tmp);
		line->curr->buff_tmp[0] = 0;
		line->curr->buff_tmp[8193] = 0;
		put_new_prompt(line);
	}
}
