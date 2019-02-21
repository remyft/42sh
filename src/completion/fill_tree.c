/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:45:40 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/21 06:45:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "put.h"
#include "ft_printf.h"

static int	get_indir(char *toget, int *i, t_tree **ternary)
{
	char			*path;
	DIR				*dir;
	struct dirent	*indir;

	path = strdup_until(&toget[*i], ':');
	dir = opendir(path);
	free(path);
	while (dir && (indir = readdir(dir)))
		if (ft_strcmp(indir->d_name, ".") && ft_strcmp(indir->d_name, ".."))
			feed_tree(indir->d_name, -1, ternary, 0);
	if (!ft_strchr(&toget[*i], ':'))
	{
		if (dir)
			closedir(dir);
		return (1);
	}
	*i += ft_strlen_ch(&toget[*i], ':') + 1;
	if (dir)
		closedir(dir);
	return (0);
}

void		fill_tree_bin(char **env, t_tree **ternary)
{
	char			*toget;
	int				i;

	toget = get_env(env, "PATH");
	if (!(*ternary = ft_memalloc(sizeof(t_tree))))
	{
		*ternary = NULL;
		return ;
	}
	(*ternary)->value = -1;
	i = 0;
	while (1)
		if (get_indir(toget, &i, ternary))
			break ;
	free(toget);
}

void		fill_tree_env(char **env, t_tree **ternary)
{
	int		i;
	char	*var;

	if (!*ternary)
	{
		if (!(*ternary = ft_memalloc(sizeof(t_tree))))
			return ;
		(*ternary)->value = -1;
	}
	i = 0;
	if (env)
		while (env[i])
		{
			var = strdup_until(env[i], '=');
			feed_tree(var, -1, ternary, 0);
			free(var);
			i++;
		}
}
