/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 03:41:24 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/07 03:42:18 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "shell_lib.h"
#include "shell.h"

static void	get_new_glob(t_line *line, t_slst *tmp, char *ptr)
{
	int		i;
	t_slst	*to_free;

	while (tmp->prev)
		tmp = tmp->prev;
	ptr++;
	ft_bzero(ptr, ft_strlen(ptr));
	while ((to_free = tmp))
	{
		i = -1;
		while (tmp->str[++i])
		{
			if (sh_is_escapable(tmp->str[i]))
				*ptr++ = '\\';
			*ptr++ = tmp->str[i];
		}
		*ptr++ = ' ';
		tmp = tmp->next;
		free(to_free->str);
		free(to_free);
	}
	i = line->len / line->nb_col;
	while (i--)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, line->lprompt), 1, ft_pchar);
}

static void	set_new_glob(t_line *line, t_slst *tmp, char *ptr)
{
	if (tmp)
	{
		get_new_glob(line, tmp, ptr);
		ft_putstr(line->curr->buff);
		line->len = ft_strlen(line->curr->buff);
		line->index = line->len;
	}
}

void		choose_tree(t_line *line)
{
	char	*ptr;
	t_slst	*tmp;

	tmp = NULL;
	if ((ptr = sh_strrchr(line->curr->buff, ' ')) && str_chrglob(ptr))
		tmp = deal_globing(ptr + 1, line->tree[1]);
	else if (!ptr && str_chrglob(line->curr->buff))
		tmp = deal_globing(line->curr->buff, line->tree[1]);
	else if (have_to_expand(line))
		deal_complet(line->tree[3], line);
	else if (!ptr || (!sh_strchr(ptr, '/') && !sh_strchr(ptr, '~')))
		deal_complet(!sh_strchr(line->curr->buff, ' ') ? line->tree[0]
				: line->tree[1], line);
	else
	{
		if (line->tree[2] || (line->tree[2] = set_tmp(line->curr->buff)))
			deal_complet(line->tree[2], line);
	}
	set_new_glob(line, tmp, ptr);
}

void		get_complet(t_line *line)
{
	if (!(*line->e_cmpl & COMPLETION) && line->curr->buff_tmp[8193])
	{
		line->curr->buff_tmp[0] = 0;
		line->curr->buff_tmp[8193] = 0;
	}
	if (!inprint(line->curr->buff))
		return ;
	choose_tree(line);
}
