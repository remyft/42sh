/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:06:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/30 14:59:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command_error.h"

int				command_error(char *progname, int err, char **cmd)
{
	static char	*error[] = {
		"", ERR_EXEC_STR, ERR_MALLOC_STR, ERR_NOT_FOUND_STR,
		ERR_NO_SUCH_FILE_STR, ERR_PERM_STR, ERR_IS_DIRECTORY_STR,
	};

	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (cmd && cmd[0])
	{
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(error[err], STDERR_FILENO);
	return (1);
}
