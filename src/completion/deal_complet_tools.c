/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_complet_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 02:17:24 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/27 17:17:38 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char	*replace_str(const char *path, const char *src,
		const char *replace)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*str;

	if (!ft_strstr(path, src))
		return (NULL);
	i = 0;
	j = 0;
	ft_find((char*)path, (char*)src, &i, &j);
	if (!(str = ft_memalloc(sizeof(char) * (ft_strlen(path) - ft_strlen(src)
						+ ft_strlen(replace) + 1))))
		return (NULL);
	k = -1;
	while (++k < i)
		str[k] = path[k];
	str[k] = '\0';
	l = -1;
	while (replace[++l])
		str[k + l] = replace[l];
	k--;
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

	stmp = ft_strrchr(buff, ' ') + 1;
	tmp = NULL;
	if (*stmp != '/')
	{
		if (*stmp == '~')
		{
			tmp = replace_str(stmp, "~", getenv("HOME"));
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
