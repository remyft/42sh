/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 03:41:24 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/04 17:04:23 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "shell_lib.h"
#include "shell_term.h"
#include "shell.h"
#include "libft.h"

static void	get_new_glob(t_line *line, t_slst *tmp, char *ptr)
{
	int		i;
	t_slst	*to_free;
	int		tmp_len;

	tmp_len = line->len;
	ft_bzero(ptr, ft_strlen(ptr));
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
	while ((to_free = tmp))
	{
		if (line->len + ft_strlen(tmp->str) > 8192)
			break;
		i = -1;
		while (tmp->str[++i])
		{
			if (sh_is_escapable(tmp->str[i]))
			{
				*ptr++ = '\\';
				line->len++;
			}
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

static void	set_new_glob(t_line *line, t_slst *tmp, char *ptr)
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

void		deal_choose_tree(t_line *line, char *ptr)
{
	if (have_to_expand(line))
		deal_complet(GET_TREE(line->tree, ENV), line);
	else if (check_is_file(line->curr->buff, line))
	{
		if (search_to_tmp(ptr))
		{
			if (GET_TREE(line->tree, TMP)
					|| (GET_TREE(line->tree, TMP) = set_tmp(line->curr->buff)))
				deal_complet(GET_TREE(line->tree, TMP), line);
		}
		else
			deal_complet(GET_TREE(line->tree, FILES), line);
	}
	else
		deal_complet(GET_TREE(line->tree, BIN), line);
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
	else
		deal_choose_tree(line, ptr);
	if (!ptr)
		set_new_glob(line, tmp, line->curr->buff);
	else
		set_new_glob(line, tmp, ptr + 1);
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
