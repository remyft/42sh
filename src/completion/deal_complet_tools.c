/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_complet_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 02:17:24 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/28 20:27:23 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
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
	else
		stmp = ft_strndup(stmp, ft_strrchr(stmp, '/') - stmp + 1);
	file = create_file_tree(stmp, NULL);
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

void	free_select(t_slct *select)
{
	if (select->next)
		free_select(select->next);
	if (select->down)
		free_select(select->down);
	if (select)
		free(select);
}
