/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_complet_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 02:17:24 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/27 13:52:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

	stmp = ft_strrchr(buff, ' ') + 1;
	if (*stmp != '/')
		stmp = ft_strndup(stmp, ft_strrchr(stmp, '/') - stmp);
	file = create_file_tree(stmp, NULL);
	if (*stmp != '/')
		free(stmp);
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
