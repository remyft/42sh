/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 10:57:02 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/31 20:50:06 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"

void	deal_prompt(t_line *line)
{
	free(line->prompt);
	if (*(line->e_cmpl) & QUOTE)
		line->prompt = ft_strdup("quote> ");
	else if (*(line->e_cmpl) & BQUOTE)
		line->prompt = *(line->e_cmpl) & DQUOTE ?
			ft_strdup("dquote bquote> ") : ft_strdup("bquote> ");
	else if (*(line->e_cmpl) & DQUOTE && *(line->e_cmpl) & ~BQUOTE)
		line->prompt = ft_strdup("dquote> ");
	else if (*(line->e_cmpl) & HDOC)
		line->prompt = ft_strdup("heredoc> ");
	else
		line->prompt = ft_strdup("$> ");
	line->lprompt = ft_strlen(line->prompt);
}

void	reset_line(t_line *line)
{
	ft_bzero(line->curr->buff, 8193);
	ft_bzero(line->curr->buff_tmp, 8194);
	line->len = 0;
	line->index = 0;
}


void	free_buff(t_line *line)
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

void	init_new_buff(t_line *line)
{
	free_buff(line);
	line->curr = ft_memalloc(sizeof(t_buff));
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
	str = ft_strdup(line->curr->buff);
	if (line->curr->next)
		str = ft_strjoinfree(str, "\n", 1);
	line->curr = line->curr->next;
	while (line->curr && line->curr->next)
	{
		str = ft_strjoinfree(str, line->curr->buff, 1);
		str = ft_strjoinfree(str, "\n", 1);
		line->curr = line->curr->next;
	}
	if (line->curr)
		str = ft_strjoinfree(str, line->curr->buff, 1);
	line->curr = begin;
	return (str);
}
