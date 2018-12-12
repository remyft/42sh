/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:57:17 by rfontain          #+#    #+#             */
/*   Updated: 2018/12/12 12:43:21 by rfontain         ###   ########.fr       */
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
	while (cp < nb_read && line->tmp[0] != 12 && (ft_isprint(line->tmp[cp])
				|| ft_isspace(line->tmp[cp])) && line->tmp[0] != 9 && line->tmp[cp] != 10)
	{
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
