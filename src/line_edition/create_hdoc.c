/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:00:50 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/27 13:52:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "token.h"

static void	deal_state(t_line *line, char c)
{
	if (c == '\'')
	{
		if (!(*(line->e_cmpl) & DQUOTE) && !(*(line->e_cmpl) & BQUOTE)
				&& !(*(line->e_cmpl) & NSTATE))
			return (change_state(line, QUOTE));
	}
	else if (c == '"')
	{
		if (!(*(line->e_cmpl) & QUOTE) && !(*(line->e_cmpl) & BQUOTE)
				&& !(*(line->e_cmpl) & NSTATE))
			return (change_state(line, DQUOTE));
	}
	else if (c == '`')
	{
		if (!(*(line->e_cmpl) & QUOTE) && !(*(line->e_cmpl) & NSTATE))
			return (change_state(line, BQUOTE));
	}
}

static int	get_new_hdoc(t_line *line, int state, t_buff *buff)
{
	if (state & WT_HDOC || *(line->e_cmpl) > 0)
	{
		if (state & WT_HDOC)
			*(line->e_cmpl) |= HDOC;
		deal_prompt(line);
		deal_continue(line);
		while (line->hdoc && line->hdoc->next)
			line->hdoc = line->hdoc->next;
		while (buff->prev)
			buff = buff->prev;
		while (line->hdoc && line->hdoc->prev)
		{
			line->hdoc->cmd = expand_word((t_token*)line->hdoc);
			line->hdoc = line->hdoc->prev;
		}
		if (line->hdoc)
			line->hdoc->cmd = expand_word((t_token*)line->hdoc);
		return (1);
	}
	deal_prompt(line);
	return (0);
}

static void	create_new_hdoc(t_line *line, int *state, int i)
{
	if (!line->hdoc)
		line->hdoc = ft_memalloc(sizeof(*line->hdoc));
	else
	{
		line->hdoc->next = ft_memalloc(sizeof(*line->hdoc));
		line->hdoc->next->prev = line->hdoc;
		line->hdoc = line->hdoc->next;
	}
	*state |= WT_HDOC;
	*state &= ~WT_SPACE;
	line->hdoc->head = &line->curr->buff[i];
	line->hdoc->len = 1;
}

static void	check_curr_hdoc(t_line *line, int *i, int *state)
{
	if (line->curr->buff[*i] == '<' && !(*state & WT_NHDOC)
			&& !(*state & NSTATE))
		*state |= WT_NHDOC;
	else if (line->curr->buff[*i] == '<' && *state & WT_NHDOC)
		*state |= *state & WT_SPACE ? UN_HDOC : WT_SPACE;
	else if (line->curr->buff[*i] != ' ' && *state & WT_SPACE)
		create_new_hdoc(line, state, *i);
	else if (line->curr->buff[*i] != ' ' && *state & WT_HDOC)
		line->hdoc->len++;
	else if (line->curr->buff[*i] == ' ' && *state & WT_HDOC)
	{
		*state &= ~WT_HDOC;
		*(line->e_cmpl) |= HDOC;
	}
	else if (*state & WT_NHDOC)
		*state &= ~WT_NHDOC;
}

int			check_hdoc(t_line *line)
{
	int		i;
	int		state;
	t_buff	*buff;

	i = -1;
	state = 0;
	buff = line->curr;
	while (line->curr->buff[++i])
	{
		if (!(state & NSTATE))
			deal_state(line, line->curr->buff[i]);
		if (!line->curr->prev && !(state & UN_HDOC))
		{
			if (line->curr->buff[i] == '\\' && !(state & NSTATE))
				state |= NSTATE;
			else if (state & NSTATE)
			{
				state &= ~NSTATE;
				if (line->curr->buff[i] == '<')
					i++;
			}
			check_curr_hdoc(line, &i, &state);
		}
	}
	return (get_new_hdoc(line, state, buff));
}
