/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_complet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 17:13:29 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/08 06:25:24 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "shell.h"
#include "libft.h"
#include "shell_lib.h"
#include "shell_term.h"

static int	deal_set(t_line *line, char *ptr, DIR *dir)
{
	char	*tmp;
	char	c;

	tmp = NULL;
	if (line->curr->buff[line->len - 1] == '/'
			|| line->curr->buff[line->len - 1] == ' ')
		return (10);
	if (ptr && *(ptr + 1) == '~')
	{
		ptr = replace_tilde(ptr, getenv("HOME"));
		tmp = ptr;
	}
	line->tree[2] = free_tree(line->tree[2]);
	if (ptr && (dir = opendir(ptr + 1)))
		c = '/';
	else
		c = ' ';
//	if (line->tmp[0] != ' ')
//	{
		ft_putchar(line->curr->buff[(line->len)] = c);
		line->curr->buff[++(line->len)] = '\0';
//	}
	if (tmp)
		free(tmp);
	if (dir)
		closedir(dir);
	return (0);
}

void		set_complet(t_line *line, int set)
{
	DIR		*dir;
	char	*ptr;
	int		tmp;

	dir = NULL;
	delete_down();
	tmp = line->tmp[0];
	*(line->e_cmpl) &= ~COMPLETION;
	line->is_putb = 0;
	ptr = sh_strrchr(line->curr->buff, ' ');
	line->tmp[0] = deal_set(line, ptr, dir);
	if (!set)
		line->tmp[0] = tmp;
	ft_bzero(line->curr->buff_tmp, ft_strlen(line->curr->buff_tmp));
	line->curr->buff_tmp[8193] = 0;
	line->index = line->len;
}
