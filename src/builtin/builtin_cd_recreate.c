/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_recreate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:56:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/02 19:57:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*search_back(char *pwd, char *origin)
{
	while (pwd > origin && *pwd != '/')
		pwd--;
	return (pwd);
}

char			*cd_recreate_path(char *pwd)
{
	char		*slsh;
	char		*ptr;

	slsh = pwd;
	while (*slsh)
	{
		if (!(ptr = ft_strchr(slsh + 1, '/')))
			if ((ptr = slsh + ft_strlen(slsh)) == slsh)
				ptr++;
		if (!ft_strncmp(slsh + 1, "./", ptr - slsh - 1))
			slsh = ft_strcpy(slsh, ptr);
		else if (!ft_strncmp(slsh + 1, "..", ptr - slsh - 1))
		{
			if ((slsh = search_back(slsh - 1, pwd)))
				slsh = ft_strcpy(slsh, ptr);
		}
		else
			slsh = ptr;
	}
	if (slsh == pwd && !*slsh)
		ft_strcpy(slsh, "/");
	return (pwd);
}
