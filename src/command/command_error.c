/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:06:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/02 16:11:26 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command_error.h"
#include "shell_env.h"

int				command_error(char *progname, int err, char **cmd, t_s_env *e)
{
	static t_error	errors[] = {
		ERR_OK_STR, ERR_NOT_FOUND_STR, ERR_NO_SUCH_FILE_STR,
		ERR_IS_DIRECTORY_STR, ERR_PERM_STR, ERR_MALLOC_STR, ERR_EXEC_STR,
		ERR_FORK_STR, ERR_BAD_FD_STR, ERR_DUP_STR,
	};

	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (cmd && cmd[0])
	{
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(errors[err].error, STDERR_FILENO);
	e->ret = errors[err].value;
	return (1);
}
