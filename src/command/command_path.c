/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:47:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/30 15:09:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command_error.h"
#include "command.h"

static int		check_access(char **path, char *cmd, char *paths, size_t len)
{
	int			error;

	if ((*path = ft_strndup(paths, len)))
		if ((*path = ft_strjoinfree(*path, "/", 1)))
			if ((*path = ft_strjoinfree(*path, cmd, 1)))
			{
				if ((error = command_access(*path, 0)) == ERR_OK_VAL)
					return (ERR_OK_VAL);
				free(*path);
				*path = NULL;
				return (error);
			}
	return (ERR_MALLOC_VAL);
}

int				command_path(char **path, char *cmd, char *paths)
{
	char		*ptr;

	if (!cmd || !paths)
		return (ERR_OK_VAL);
	if (ft_strrchr(cmd, '/'))
		return (command_access((*path = ft_strdup(cmd)), 1));
	ptr = paths;
	while (*ptr)
	{
		if (*ptr == ':')
		{
			if (check_access(path, cmd, paths, ptr - paths) == ERR_OK_VAL)
				return (ERR_OK_VAL);
			paths = ptr + 1;
		}
		ptr++;
	}
	return (check_access(path, cmd, paths, ptr - paths));
}
