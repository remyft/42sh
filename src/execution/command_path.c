/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:47:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/21 20:43:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execution_error.h"

static char		*check_access(char *cmd, char *ptr, char *paths)
{
	char		*path;

	if ((path = ft_strndup(paths, ptr - paths)))
		if ((path = ft_strjoinfree(path, "/", 1)))
			if ((path = ft_strjoinfree(path, cmd, 1)))
			{
				if (!access(path, F_OK))
					return (path);
				free(path);
			}
	return (NULL);
}

int				path_command(char **path, char *cmd, char *paths)
{
	char		*ptr;

	if (!cmd || !paths)
		return (ERR_OK_VAL);
	if (ft_strrchr(cmd, '/'))
		return ((*path = ft_strdup(cmd)) ? ERR_OK_VAL : ERR_MALLOC_VAL);
	ptr = paths;
	while (*ptr)
	{
		if (*ptr == ':')
		{
			if ((*path = check_access(cmd, ptr, paths)))
				return (ERR_OK_VAL);
			paths = ptr + 1;
		}
		ptr++;
	}
	*path = check_access(cmd, ptr, paths);
	return ((path) ? ERR_OK_VAL : ERR_NOT_FOUND_VAL);
}
