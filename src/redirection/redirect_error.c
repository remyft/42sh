/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:29:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/26 16:48:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_env.h"
#include "redirection_errors.h"
#include "redirection.h"

int				redirect_error(int err, char *redirect_arg, t_s_env *e)
{
	static char	*error[] = {
		NULL,
		MALLOC_STR,
		AMBIGOUS_STR,
		BAD_FD_STR
	};

	e->ret = 130;
	if (err == ERR_FREE_ALL)
		return (1);
	ft_putstr_fd(e->progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(redirect_arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error[err], STDERR_FILENO);
	e->ret = 2;
	return (1);
}
