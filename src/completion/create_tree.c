/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:15:52 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/27 19:12:59 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "put.h"
#include "shell_lib.h"
#include <dirent.h>

char		*add_escape(char *str, int nb)
{
	char	*esc;
	int		i;
	int		j;

	if (!(esc = ft_memalloc(sizeof(char) * (ft_strlen(str) + nb + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (sh_is_escapable(str[i]))
			esc[j++] = '\\';
		esc[j++] = str[i];
	}
	return (esc);
}

t_tree		*create_bin_tree(char **env)
{
	t_tree	*ternary;

	if (!env)
		return (NULL);
	ternary = NULL;
	fill_tree_bin(env, &ternary);
	set_psblty(ternary);
	return (ternary);
}

t_tree		*create_file_tree(char *path, t_tree *tern)
{
	struct dirent	*indir;
	DIR				*dir;
	int				is_esc;
	char			*tmp;

	if (!path || !(dir = opendir(path)))
		return (NULL);
	if (!tern)
	{
		tern = ft_memalloc(sizeof(t_tree));
		tern->value = -1;
	}
	while ((indir = readdir(dir)))
		if ((is_esc = sh_str_isescape(indir->d_name)))
		{
			tmp = add_escape(indir->d_name, is_esc);
			feed_tree(tmp, indir->d_type, &tern, 0);
			free(tmp);
		}
		else
			feed_tree(indir->d_name, indir->d_type, &tern, 0);
	set_psblty(tern);
	closedir(dir);
	return (tern);
}
