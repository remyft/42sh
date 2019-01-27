/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_complet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 17:13:29 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/27 17:41:17 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "21sh.h"
#include "shell_lib.h"

static void	deal_set(t_line *line, char *ptr, DIR *dir)
{
	char	*tmp;

	tmp = NULL;
	if (ptr && *(ptr + 1) == '~')
	{
		ptr = replace_str(ptr,  "~", getenv("HOME"));
		tmp = ptr;
	}
	if (ptr && (dir = opendir(ptr + 1)))
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
	if (tmp)
		free(tmp);
	if (dir)
		closedir(dir);
}

void		set_complet(t_line *line)
{
	DIR		*dir;
	char	*ptr;

	dir = NULL;
	delete_down();
	*(line->e_cmpl) &= ~COMPLETION;
	line->is_putb = 0;
	ptr = sh_strrchr(line->curr->buff, ' ');
	deal_set(line, ptr, dir);
	line->tmp[0] = 0;
	ft_bzero(line->curr->buff_tmp, 8194);
	line->index = line->len;
}
