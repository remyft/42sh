/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:49:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/21 22:50:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "execution_error.h"
#include <stdio.h>
int				access_command(char *path)
{
	if (!path)
		return (ERR_NOT_FOUND_VAL);
	if (access(path, F_OK))
		return (ERR_NOT_FOUND_VAL);
	if (access(path, X_OK))
		return (ERR_PERM_VAL);
	return (ERR_OK_VAL);
}
