/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_complet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 17:13:29 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/28 19:17:23 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "shell.h"
#include "libft.h"
#include "shell_lib.h"
#include "shell_term.h"
#include "quote_removal.h"

static char	get_char(char *ptr, DIR *dir, char *buff)
{
	char	c;
	char	*tmp;

	if (ptr && ptr != buff)
		ptr++;
	tmp = ft_strdup(ptr);
	check_str(ptr);
	if (ptr && (dir = opendir(ptr)))
		c = '/';
	else
		c = ' ';
	ft_strcpy(ptr, tmp);
	free(tmp);
	if (dir)
		closedir(dir);
	return (c);
}

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
	c = get_char(ptr, dir, line->curr->buff);
	if (line->tmp[0] != ' ' && line->tmp[0] != '/')
	{
		ft_putchar(line->curr->buff[(line->len)] = c);
		line->curr->buff[++(line->len)] = '\0';
	}
	else
		line->curr->buff[line->len] = '\0';
	if (tmp)
		free(tmp);
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
	if (!(ptr = sh_strrchr(line->curr->buff, ' ')))
		ptr = line->curr->buff;
	line->tmp[0] = deal_set(line, ptr, dir);
	if (!set)
		line->tmp[0] = tmp;
	free(line->curr->buff_tmp);
	line->curr->buff_tmp = NULL;
	line->index = line->len;
}
