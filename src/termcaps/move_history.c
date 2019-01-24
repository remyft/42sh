/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 05:00:51 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/24 01:45:35 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	up_arrow(t_line *line)
{
	int			i;
	size_t		len;

	if (*line->e_cmpl & COMPLETION && line->is_putb)
	{
		line->key = UP;
		return (get_complet(line));
	}
	len = ft_strlen(line->curr->buff_tmp);
	i = ft_strlen(line->curr->buff);
	if (line->hist && line->hist->next && ((ft_strcmp(line->hist->content, line->curr->buff) == 0 && line->curr->buff_tmp[8193]) || line->hist != line->hist->begin))
	{
		if (line->hist->tmp)
			free(line->hist->tmp);
		line->hist->tmp = ft_strdup(line->curr->buff);
		line->hist = line->hist->next;
		while (line->hist->next && (ft_strstr(line->hist->content, line->curr->buff_tmp) != line->hist->content || line->hist->c_size <= len || ft_strcmp(line->hist->content, line->curr->buff) == 0))
			line->hist = line->hist->next;
		while (line->hist->prev && (ft_strstr(line->hist->content, line->curr->buff_tmp) != line->hist->content || line->hist->c_size <= len))
			line->hist = line->hist->prev;
	}
	else if (line->hist && !line->curr->buff_tmp[8193])
	{
		len = ft_strlen(line->curr->buff);
		while (line->hist->next && (ft_strstr(line->hist->content, line->curr->buff) != line->hist->content || line->hist->c_size <= len))
			line->hist = line->hist->next;
		if (line->hist != line->hist->begin && (ft_strstr(line->hist->content, line->curr->buff) != line->hist->content || line->hist->c_size <= len))
			while (line->hist->prev)
				line->hist = line->hist->prev;
		ft_strcpy(line->curr->buff_tmp, line->curr->buff);
		line->curr->buff_tmp[8193] = 1;
	}
	if (line->hist && ft_strstr(line->hist->content, line->curr->buff_tmp) == line->hist->content && line->hist->c_size > len)
	{
		ft_bzero(line->curr->buff, i);
		if (line->hist->tmp)
			ft_strcpy(line->curr->buff, line->hist->tmp);
		else
			ft_strcpy(line->curr->buff, line->hist->content);
	}
	go_home(line);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	put_prompt(line->prompt);
	ft_putstr(line->curr->buff);
	line->index = ft_strlen(line->curr->buff);
	line->len = line->index;
}

void	down_arrow(t_line *line)
{
	int		i;
	size_t	len;
	
	if (*line->e_cmpl & COMPLETION && line->is_putb)
	{
		line->key = DOWN;
		return (get_complet(line));
	}
	len = ft_strlen(line->curr->buff_tmp);
	i = ft_strlen(line->curr->buff);
	if (line->hist && line->hist->prev)
	{
		if (line->hist->tmp)
			free(line->hist->tmp);
		line->hist->tmp = ft_strdup(line->curr->buff);
		line->hist = line->hist->prev;
		while (line->hist->prev && (ft_strstr(line->hist->content, line->curr->buff_tmp) != line->hist->content || line->hist->c_size <= len || ft_strcmp(line->hist->content, line->curr->buff) == 0))
			line->hist = line->hist->prev;
		if (ft_strstr(line->hist->content, line->curr->buff_tmp) == line->hist->content && line->hist->c_size > len)
		{
			ft_bzero(line->curr->buff, i);
			if (line->hist->tmp)
				ft_strcpy(line->curr->buff, line->hist->tmp);
			else
				ft_strcpy(line->curr->buff, line->hist->content);
		}
		else
		{
			ft_bzero(line->curr->buff, i);
			ft_strcpy(line->curr->buff, line->curr->buff_tmp);
		}
	}
	else if (line->hist && line->curr->buff_tmp[8193])
	{
		ft_bzero(line->curr->buff, i);
		ft_strcpy(line->curr->buff, line->curr->buff_tmp);
		ft_bzero(line->curr->buff_tmp, 8194);
	}
	go_home(line);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	put_prompt(line->prompt);
	ft_putstr(line->curr->buff);
	line->index = ft_strlen(line->curr->buff);
	line->len = line->index;
}
