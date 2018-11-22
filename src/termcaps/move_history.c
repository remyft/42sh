/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 05:00:51 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/22 05:17:03 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	up_arrow(t_line *line)
{
	int			i;
	size_t		len;

	len = ft_strlen(line->buff_tmp);
	i = ft_strlen(line->buff);
	if (line->curr && line->curr->next && ((ft_strcmp(line->curr->content, line->buff) == 0 && line->buff_tmp[8193]) || line->curr != line->curr->begin))
	{
		if (line->curr->tmp)
			free(line->curr->tmp);
		line->curr->tmp = ft_strdup(line->buff);
		line->curr = line->curr->next;
		while (line->curr->next && (ft_strstr(line->curr->content, line->buff_tmp) != line->curr->content || line->curr->c_size <= len || ft_strcmp(line->curr->content, line->buff) == 0))
			line->curr = line->curr->next;
		while (line->curr->prev && (ft_strstr(line->curr->content, line->buff_tmp) != line->curr->content || line->curr->c_size <= len))
			line->curr = line->curr->prev;
	}
	else if (line->curr->next)
	{
		len = ft_strlen(line->buff);
		while (line->curr->next && (ft_strstr(line->curr->content, line->buff) != line->curr->content || line->curr->c_size <= len))
			line->curr = line->curr->next;
		if (line->curr != line->curr->begin && (ft_strstr(line->curr->content, line->buff) != line->curr->content || line->curr->c_size <= len))
			while (line->curr->prev)
				line->curr = line->curr->prev;
		ft_strcpy(line->buff_tmp, line->buff);
		line->buff_tmp[8193] = 1;
	}
	if (line->curr && ft_strstr(line->curr->content, line->buff_tmp) == line->curr->content && line->curr->c_size > len)
	{
		ft_bzero(line->buff, i);
		if (line->curr->tmp)
			ft_strcpy(line->buff, line->curr->tmp);
		else
			ft_strcpy(line->buff, line->curr->content);
	}
	go_home(line);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	put_prompt(line->prompt);
	ft_putstr(line->buff);
	line->index = ft_strlen(line->buff);
	line->len = line->index;
}

void	down_arrow(t_line *line)
{
	int		i;
	size_t	len;

	len = ft_strlen(line->buff_tmp);
	i = ft_strlen(line->buff);
	if (line->curr && line->curr->prev)
	{
		if (line->curr->tmp)
			free(line->curr->tmp);
		line->curr->tmp = ft_strdup(line->buff);
		line->curr = line->curr->prev;
		while (line->curr->prev && (ft_strstr(line->curr->content, line->buff_tmp) != line->curr->content || line->curr->c_size <= len || ft_strcmp(line->curr->content, line->buff) == 0))
			line->curr = line->curr->prev;
		if (ft_strstr(line->curr->content, line->buff_tmp) == line->curr->content && line->curr->c_size > len)
		{
			ft_bzero(line->buff, i);
			if (line->curr->tmp)
				ft_strcpy(line->buff, line->curr->tmp);
			else
				ft_strcpy(line->buff, line->curr->content);
		}
		else
		{
			ft_bzero(line->buff, i);
			ft_strcpy(line->buff, line->buff_tmp);
		}
	}
	else if (line->curr && line->buff_tmp[8193])
	{
		ft_bzero(line->buff, i);
		ft_strcpy(line->buff, line->buff_tmp);
		ft_bzero(line->buff_tmp, 8194);
	}
	go_home(line);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	put_prompt(line->prompt);
	ft_putstr(line->buff);
	line->index = ft_strlen(line->buff);
	line->len = line->index;
}
