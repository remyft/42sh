/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:15:52 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 12:56:31 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "put.h"
#include <dirent.h>

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

	if (!path)
		return (NULL);
	if (!(dir = opendir(path)))
		return (NULL);
	if (!tern)
	{
		tern = ft_memalloc(sizeof(t_tree));
		tern->value = -1;
	}
	while ((indir = readdir(dir)))
		feed_tree(indir->d_name, indir->d_type, &tern, 0);
	set_psblty(tern);
	closedir(dir);
	return (tern);
}
