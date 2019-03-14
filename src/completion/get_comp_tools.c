/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comp_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 17:00:18 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/14 15:48:32 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "libft.h"
#include "shell_term.h"

int			check_is_file(char *buff, t_line *line)
{
	int		i;

	i = line->len - 1;
	while (i >= 0 && !ft_strchr("&;| ", buff[i]))
		i--;
	while (i >= 0 && (buff[i] == ' ' || buff[i] == '\t'))
		i--;
	if (i == -1 || ft_strchr(";&|", buff[i]))
		return (0);
	return (1);
}

int			search_to_tmp(char *buff)
{
	int		i;

	i = -1;
	while (buff[++i])
		if (buff[i] == '~' || buff[i] == '/')
			return (1);
		else if (buff[i] == '*')
			return (0);
	return (0);
}

static int	erase_complet(char *ptr, t_line *line)
{
	ft_bzero(ptr, ft_strlen(ptr));
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
	return (line->len);
}

static void	get_new_glob(t_line *line, t_slst *tmp, char *ptr)
{
	int		i;
	t_slst	*to_free;
	int		tmp_len;

	tmp_len = erase_complet(ptr, line);
	while ((to_free = tmp))
	{
		if (line->len + ft_strlen(tmp->str) > 8192)
			break ;
		i = -1;
		while (tmp->str[++i])
		{
			*ptr++ = tmp->str[i];
			line->len++;
		}
		*ptr++ = ' ';
		line->len++;
		tmp = tmp->next;
		free(to_free->str);
		free(to_free);
	}
	i = tmp_len / line->nb_col;
	while (i--)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, line->lprompt), 1, ft_pchar);
}

void		set_new_glob(t_line *line, t_slst *tmp, char *ptr)
{
	if (tmp)
	{
		while (tmp->prev)
			tmp = tmp->prev;
		get_new_glob(line, tmp, ptr);
		ft_putstr(line->curr->buff);
		line->len = ft_strlen(line->curr->buff);
		line->index = line->len;
	}
}
