/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 10:38:58 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 11:03:58 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

static int	del_hdoc(t_line *line, t_state *tmp)
{
	if (line->hdoc->next)
	{
		line->hdoc = line->hdoc->next;
		free(line->hdoc->prev->cmd);
		free(line->hdoc->prev);
		line->hdoc->prev = NULL;
		free(tmp->cmd);
		free(tmp);
		return (0);
	}
	else
	{
		free(line->hdoc->cmd);
		free(line->hdoc);
		line->hdoc = NULL;
		*(line->e_cmpl) &= ~HDOC;
		deal_prompt(line);
		free(tmp->cmd);
		free(tmp);
		return (1);
	}
}

int			deal_hdoc(t_line *line)
{
	t_state *tmp;

	if (!line->curr->prev)
		return (0);
	while (line->hdoc && line->hdoc->prev)
		line->hdoc = line->hdoc->prev;
	tmp = ft_memalloc(sizeof(t_state));
	tmp->head = 0;
	tmp->tail = ft_strlen(line->curr->buff);
	tmp->cmd = expand_word(line->curr->buff, (t_token*)tmp);
	if (tmp->cmd && line->hdoc && line->hdoc->cmd
			&& ft_strcmp(tmp->cmd, line->hdoc->cmd) == 0)
		return (del_hdoc(line, tmp));
	free(tmp->cmd);
	free(tmp);
	return (0);
}

int			deal_continue(t_line *line)
{
	if (*(line->e_cmpl) & QUOTE || *(line->e_cmpl) & DQUOTE
			|| *(line->e_cmpl) & BQUOTE || *(line->e_cmpl) & HDOC
			|| *(line->e_cmpl) & WT_HDOC)
	{
		line->curr->next = ft_memalloc(sizeof(t_buff));
		line->curr->next->prev = line->curr;
		line->curr = line->curr->next;
		line->index = 0;
		line->len = 0;
		return (1);
	}
	return (0);
}

void		change_state(t_line *line, int state)
{
	if (*(line->e_cmpl) & state)
		*(line->e_cmpl) &= ~state;
	else
		*(line->e_cmpl) |= state;
	return ;
}
