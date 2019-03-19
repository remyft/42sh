/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 10:57:02 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/19 16:32:10 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"
#include "shell.h"

void	reset_line(t_line *line)
{
	ft_bzero(line->curr->buff, 8193);
	ft_bzero(line->curr->buff_tmp, 8194);
	line->len = 0;
	line->index = 0;
}

void	init_new_buff(t_line *line)
{
	free_buff(line);
	if (!(line->curr = ft_memalloc(sizeof(t_buff))))
	{
		line->shell_loop = 0;
		return ;
	}
	line->beg_buff = line->curr;
	line->index = 0;
	line->len = 0;
}

char	*listnjoin(t_line *line)
{
	char	*str;
	t_buff	*begin;

	while (line->curr->prev)
		line->curr = line->curr->prev;
	begin = line->curr;
	if (!(str = ft_strdup(line->curr->buff)))
		return (NULL);
	if (line->curr->next)
		if (!(str = ft_strjoinfree(str, "\n", 1)))
			return (NULL);
	line->curr = line->curr->next;
	while (line->curr && line->curr->next)
	{
		if (!(str = ft_strjoinfree(str, line->curr->buff, 1)))
			return (NULL);
		if (!(str = ft_strjoinfree(str, "\n", 1)))
			return (NULL);
		line->curr = line->curr->next;
	}
	if (line->curr)
		if (!(str = ft_strjoinfree(str, line->curr->buff, 1)))
			return (NULL);
	line->curr = begin;
	return (str);
}
