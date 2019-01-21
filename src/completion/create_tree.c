/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:15:52 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/20 21:33:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	feed_branch(t_tree **tern, char *str, int lvl)
{
	t_tree	*prev;
	int		len;

	prev = NULL;
	while (*tern && (*tern)->value != *str)
	{
		prev = *tern;
		(*tern) = (*str < (*tern)->value) ? (*tern)->left : (*tern)->right;
	}
	if (!(*tern))
	{
		*tern = ft_memalloc(sizeof(t_tree));
		if (*str < prev->value)
			prev->left = *tern;
		else
			prev->right = *tern;
		(*tern)->value = *str;
		(*tern)->prev = prev->prev;
		if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
			(*tern)->max_len = lvl + len;
	}
	else
		if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
			(*tern)->max_len = lvl + len;
}

void		feed_tree(char *str, unsigned char type, t_tree **tern, int lvl)
{
	t_tree		*begin;
	int			len;

	begin = NULL;
	if ((*tern)->value >= 0)
	{
		begin = *tern;
		feed_branch(tern, str, lvl);
	}
	else
	{
		(*tern)->value = *str;
		if (!*str)
		{
			(*tern)->len = lvl;
			(*tern)->type = type;
		}
		if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
			(*tern)->max_len = lvl + len;
	}
	if (!(*tern)->tern_next && *str)
	{
		(*tern)->tern_next = ft_memalloc(sizeof(t_tree));
		(*tern)->tern_next->prev = (*tern);
		(*tern)->tern_next->value = -1;
	}
	if (*str)
		feed_tree(str + 1, type, &((*tern)->tern_next), lvl + 1);
	*tern = begin ? begin : *tern;
}

static void	fill_tree_bin(char **env, t_tree **ternary)
{
	char			*toget;
	struct dirent	*indir;
	DIR				*dir;
	int				i;
	char			*path;

	toget = get_env(env, "PATH");
	if (!(*ternary = ft_memalloc(sizeof(t_tree))))
		exit(1);
	(*ternary)->value = -1;
	i = 0;
	while (1)
	{
		path = strdup_until(&toget[i], ':');
		dir = opendir(path);
		free(path);
		while (dir && (indir = readdir(dir)))
			if (ft_strcmp(indir->d_name, ".") && ft_strcmp(indir->d_name, ".."))
				feed_tree(indir->d_name, indir->d_type, ternary, 0);
		if (!ft_occuc(&toget[i], ':'))
			break ;
		i += ft_strlen_ch(&toget[i], ':') + 1;
		if (dir)
			closedir(dir);
	}
	if (dir)
		closedir(dir);
	free(toget);
}

static void	fill_tree_env(char **env, t_tree **ternary)
{
	int		i;
	char	*var;

	i = 0;
	while (env[i])
	{
		var = strdup_until(env[i], '=');
		feed_tree(var, 0, ternary, 0);
		free(var);
		i++;
	}
}

t_tree		*create_bin_tree(char **env)
{
	t_tree	*ternary;

	if (!env)
		return (NULL);
	ternary = NULL;
	fill_tree_bin(env, &ternary);
	fill_tree_env(env, &ternary);
	set_psblty(ternary);
	return (ternary);
}

t_tree		*create_file_tree(char *path)
{
	struct dirent	*indir;
	DIR				*dir;
	t_tree			*tern;

	if (!path)
		return (NULL);
	if (!(dir = opendir(path)))
		return (NULL);
	tern = ft_memalloc(sizeof(t_tree));
	tern->value = -1;
	while ((indir = readdir(dir)))
		feed_tree(indir->d_name, indir->d_type, &tern, 0);
	set_psblty(tern);
	closedir(dir);
	return (tern);
}

