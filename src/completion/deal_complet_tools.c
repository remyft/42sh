/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_complet_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 02:17:24 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/29 15:17:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "shell_lib.h"

char	*replace_tilde(const char *path, const char *replace)
{
	int		j;
	int		k;
	int		l;
	char	*str;

	if (!(str = ft_memalloc(sizeof(char) * (ft_strlen(path)
						+ ft_strlen(replace)))))
		return (NULL);
	k = -1;
	while (path[++k] != '~')
		str[k] = path[k];
	l = -1;
	while (replace[++l])
		str[k + l] = replace[l];
	k--;
	j = 1;
	while (path[++k + j])
		str[k + l] = path[k + j];
	str[k + l] = '\0';
	return (str);
}

int		inprint(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (ft_isprint(str[i]))
			return (1);
	return (0);
}

t_tree	*set_tmp(char *buff)
{
	t_tree	*file;
	char	*stmp;
	char	*tmp;

	stmp = sh_strrchr(buff, ' ') + 1;
	tmp = NULL;
	if (*stmp != '/')
	{
		if (*stmp == '~')
		{
			tmp = replace_tilde(stmp, getenv("HOME"));
			stmp = ft_strndup(tmp, ft_strrchr(tmp, '/') - tmp);
		}
		else
			stmp = ft_strndup(stmp, ft_strrchr(stmp, '/') - stmp);
	}
	file = create_file_tree(stmp, NULL);
	if (*stmp != '/' || tmp)
		free(stmp);
	if (tmp)
		free(tmp);
	return (file);
}

int		str_chrglob(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' || str[i] == '[' || str[i] == '?')
			return (1);
		i++;
	}
	return (0);
}
