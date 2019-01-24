/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:49:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/24 08:27:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "execution_error.h"
#include <sys/stat.h>

int				access_command(char *path)
{
	struct stat	buf;

	if (!path)
		return (ERR_NOT_FOUND_VAL);
	if (access(path, F_OK))
		return (ERR_NOT_FOUND_VAL);
	if (access(path, X_OK))
		return (ERR_PERM_VAL);
	if (stat(path, &buf))
		return (ERR_NOT_FOUND_VAL);
	if (S_ISDIR(buf.st_mode))
		return (ERR_IS_DIRECTORY_VAL);
	return (ERR_OK_VAL);
}
