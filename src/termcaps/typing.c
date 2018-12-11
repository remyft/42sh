/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:57:17 by rfontain          #+#    #+#             */
/*   Updated: 2018/12/11 17:44:10 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	ft_strspace(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (!ft_isspace(str[i]))
			return (0);
	return (1);
}*/

void		change_state(t_line *line, int state)
{
	if (*(line->e_cmpl) & state)
		*(line->e_cmpl) &= ~state;
	else
		*(line->e_cmpl) |= state;
	return ;
}


void		deal_state(t_line *line, char c)
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
	else if (!line->curr->prev && c == '<' && line->len >= 1
			&& line->curr->buff[line->len - 1] == '<')
	{
		if (line->len - 2 >= 0 && line->curr->buff[line->len - 2] == '<')
		{
			if (line->len >= 3 && line->curr->buff[line->len - 3] == '<'
					&& !(*(line->e_cmpl) & QUOTE || *(line->e_cmpl) & DQUOTE
						|| *(line->e_cmpl) & BQUOTE))
				*(line->e_cmpl) |= NSTATE;
			else
				*(line->e_cmpl) &= ~WT_SPACE;
			return ;
		}
		if (!(*(line->e_cmpl) & QUOTE) && !(*(line->e_cmpl) & DQUOTE)
				&& !(*(line->e_cmpl) & BQUOTE) && !(*(line->e_cmpl) & NSTATE))
		{
			*(line->e_cmpl) &= ~WT_HDOC;
			*(line->e_cmpl) |= WT_SPACE;
		}
	}
}

static void	deal_hdoc(t_line *line, char c)
{
	char	*tmp;
	int		i;

	if (!line->curr->prev && *(line->e_cmpl) & WT_SPACE)
	{
		if (c == '<')
		{
			if (line->hdoc && line->hdoc->val && line->hdoc->val[(i = ft_strlen(line->hdoc->val)) - 1] == ' ')
			line->hdoc->val[i - 1] = 0;
			return (del_all_state(line));
		}
		if (c != ' ' && c != 10 && !(*(line->e_cmpl) & WT_HDOC))
		{
			if (!line->hdoc)
			{
				line->hdoc = ft_memalloc(sizeof(t_hdlist));
				line->hdoc->val = ft_memalloc(11);
			}
			else
			{
				line->hdoc->next = ft_memalloc(sizeof(t_hdlist));
				line->hdoc->next->prev = line->hdoc;
				line->hdoc = line->hdoc->next;
				line->hdoc->val = ft_memalloc(11);
			}
			*(line->e_cmpl) |= WT_HDOC;
		}
		if (*(line->e_cmpl) & WT_HDOC)
		{
				if ((i = ft_strlen(line->hdoc->val)) > 0 && i % 10 != 0)
					line->hdoc->val[i] = c;
				else
				{
					tmp = ft_strdup(line->hdoc->val);
					free(line->hdoc->val);
					line->hdoc->val = ft_memalloc(i + 11);
					ft_strcpy(line->hdoc->val, tmp);
					line->hdoc->val[i] = c;
					free(tmp);
				}
		}
	}
}

void		get_typing(t_line *line, int nb_read)
{
	int		cp;
	int		j;
	char	cbis;
	char	tchar;

	cp = 0;
	j = -1;
	line->tmp[nb_read] = '\0';
	if (ft_isprint(line->tmp[0]))
		ft_bzero(line->curr->buff_tmp, 8194);
	if (line->tmp[0] == 10)
		if (*(line->e_cmpl) & WT_HDOC)
		{
			*(line->e_cmpl) |= HDOC;
			return ;
		}
	while (cp < nb_read && line->tmp[0] != 12 && (ft_isprint(line->tmp[cp])
				|| ft_isspace(line->tmp[cp])) && line->tmp[0] != 9 && line->tmp[cp] != 10)
	{
		deal_hdoc(line, line->tmp[cp]);
		deal_state(line, line->tmp[cp]);
		tchar = line->curr->buff[line->index + 1];
		if (line->index != line->len)
			line->curr->buff[line->index + 1] = line->curr->buff[line->index];
		line->curr->buff[line->index++] = line->tmp[cp];
		line->len++;
		j = 1;
		ft_putchar(line->tmp[cp++]);
		if (line->index != line->len)
		{
			while (line->index + j < line->len)
			{
				cbis = line->curr->buff[line->index + j];
				line->curr->buff[line->index + j] = tchar;
				tchar = cbis;
				j++;
			}
			tputs(tgetstr("sc", NULL), 1, ft_pchar);
			ft_putstr(&(line->curr->buff[line->index]));
			tputs(tgetstr("rc", NULL), 1, ft_pchar);
		}
	}
}
