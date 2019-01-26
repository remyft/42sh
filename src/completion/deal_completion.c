/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:38:48 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/26 15:54:22 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "put.h"

static void	put_cpl_screen(t_line *line, int nb_ret)
{
	size_t	j;

	while (nb_ret-- + 1)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, ft_strlen(line->prompt)), 1, ft_pchar);
	j = 0;
	while (j < line->len)
	{
		tputs(tgetstr("dc", NULL), 1, ft_pchar);
		j++;
	}
	ft_putstr(line->curr->buff);
	line->len = ft_strlen(line->curr->buff);
	line->index = line->len;
}

static void	deal_complet(t_tree *file, t_line *line)
{
	int		put;
	int		nb_ret;

	put = 0;
	nb_ret = 0;
	if (!line->curr->buff_tmp[8193])
	{
		ft_strcpy(line->curr->buff_tmp, line->curr->buff);
		line->curr->buff_tmp[8193] = 1;
	}
	else
		put = 1;
	if ((put = put_complet(file, &put, line, &nb_ret)) == 1)
	{
		*line->e_cmpl |= COMPLETION;
		line->tmp[0] = 10;
	}
	else if (put == -1)
	{
		line->is_putb = 0;
		line->tmp[0] = 0;
		return ;
	}
	put_cpl_screen(line, nb_ret);
}

void		set_complet(t_line *line)
{
	DIR		*dir;

	dir = NULL;
	delete_down();
	*(line->e_cmpl) &= ~COMPLETION;
	line->is_putb = 0;
	if (ft_strrchr(line->curr->buff, ' ')
			&& (dir = opendir(ft_strrchr(line->curr->buff, ' ') + 1)))
	{
		if (line->tree[2])
			free_tree(line->tree[2]);
		line->tree[2] = NULL;
		ft_putchar(line->curr->buff[line->len] = '/');
		line->curr->buff[++(line->len)] = '\0';
	}
	else
	{
		ft_putchar(line->curr->buff[(line->len)] = ' ');
		line->curr->buff[++(line->len)] = '\0';
	}
	if (dir)
		closedir(dir);
	line->tmp[0] = 0;
	ft_bzero(line->curr->buff_tmp, 8194);
	line->index = line->len;
}

static void	get_new_glob(t_line *line, t_slst *tmp, char *ptr)
{
	int i;

	while (tmp->prev)
		tmp = tmp->prev;
	ptr++;
	ft_bzero(ptr, ft_strlen(ptr));
	while (tmp)
	{
		i = -1;
		while (tmp->str[++i])
		{
			if (!ft_isalnum(tmp->str[i]) && tmp->str[i] != '/'
					&& tmp->str[i] != '.' && tmp->str[i] != '_'
					&& tmp->str[i] != '-')
				*ptr++ = '\\';
			*ptr = tmp->str[i];
			ptr++;
		}
		*ptr++ = ' ';
		tmp = tmp->next;
	}
	i = line->len / line->nb_col;
	while (i--)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, line->lprompt), 1, ft_pchar);
}

void		get_complet(t_line *line)
{
	char	*ptr;
	t_slst	*tmp;

	tmp = NULL;
	if (!inprint(line->curr->buff))
		return ;
	if ((ptr = ft_strrchr(line->curr->buff, ' ')) && str_chrglob(ptr))
		tmp = deal_globing(ptr + 1, line->tree[1]);
	else if (!ft_strchr(line->curr->buff, ' ')
			|| !ft_strchr(ft_strrchr(line->curr->buff, ' '), '/'))
		deal_complet(!ft_strchr(line->curr->buff, ' ') ? line->tree[0]
				: line->tree[1], line);
	else
	{
		if (line->tree[2] || (line->tree[2] = set_tmp(line->curr->buff)))
			deal_complet(line->tree[2], line);
	}
	if (tmp)
	{
		get_new_glob(line, tmp, ptr);
		ft_putstr(line->curr->buff);
		line->len = ft_strlen(line->curr->buff);
		line->index = line->len;
	}
}
