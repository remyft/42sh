/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:47:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/13 17:01:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command_error.h"
#include "command.h"

static int		check_access(char **path, char *cmd, char *paths, size_t len)
{
	int			error;

	error = ERR_MALLOC;
	if (!*cmd || !ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		error = ERR_NOT_FOUND;
	else if ((*path = ft_strndup(paths, len)))
		if ((*path = ft_strjoinfree(*path, "/", 1)))
			if ((*path = ft_strjoinfree(*path, cmd, 1)))
			{
				if ((error = command_access(*path, cmd)) == ERR_OK)
					return (ERR_OK);
				ft_strdel(path);
				return (error);
			}
	ft_strdel(path);
	return (error);
}

int				command_path(char **path, char *cmd, char *paths)
{
	char		*ptr;

	if (!cmd || !paths)
		return (ERR_NO_SUCH_FILE);
	if (ft_strrchr(cmd, '/'))
		return ((*path = ft_strdup(cmd)) ? ERR_OK : ERR_MALLOC);
	ptr = paths;
	while (*ptr)
	{
		if (*ptr == ':')
		{
			if (check_access(path, cmd, paths, ptr - paths) == ERR_OK)
				return (ERR_OK);
			paths = ptr + 1;
		}
		ptr++;
	}
	return (check_access(path, cmd, paths, ptr - paths));
}
