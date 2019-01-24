/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_open_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:30:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/24 07:30:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/syslimits.h>
#include "libft.h"
#include "shell_env.h"

int				redirect_open_error(char *filename, t_s_env *e)
{
	ft_putstr_fd(e->progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (access(filename, F_OK))
		ft_putstr_fd("no such file or directory: ", STDERR_FILENO);
	else if (ft_strlen(filename) > NAME_MAX)
		ft_putstr_fd("file name too long: ", STDERR_FILENO);
	else
		ft_putstr_fd("permission denied: ", STDERR_FILENO);
	ft_putendl_fd(filename, STDERR_FILENO);
	return (1);
}
