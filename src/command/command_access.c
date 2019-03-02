/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:49:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/01 17:47:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include "command_error.h"

int				command_access(char *path, int absolute_path)
{
	struct stat	buf;

	if (!path)
		return (ERR_MALLOC);
	if (access(path, F_OK))
		return ((absolute_path) ? ERR_NO_SUCH_FILE : ERR_NOT_FOUND);
	if (access(path, X_OK))
		return (ERR_PERM);
	if (stat(path, &buf))
		return (ERR_NOT_FOUND);
	if (S_ISDIR(buf.st_mode))
		return (ERR_IS_DIRECTORY);
	return (ERR_OK);
}
