/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 19:36:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 20:09:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_env.h"

int				builtin_env_error(int err, char c, t_e_opt *opt)
{
	static char	*errors[] = {
		NULL, MALLOC_STR, ILLEGAL_OPTION_STR, NEED_ARG_STR, NO_SUCH_FILE_STR,
	};

	ft_putstr_fd(opt->cmdname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(errors[err], STDERR_FILENO);
	if (c)
	{
		ft_putstr_fd(" -- ", STDERR_FILENO);
		ft_putchar_fd(c, STDERR_FILENO);
		ft_putstr_fd("\nusage: env [-iv] [-P utilpath] ", STDERR_FILENO);
		ft_putstr_fd("[-S string] [-u name]", STDERR_FILENO);
		ft_putstr_fd("\n           [name=value ...] ", STDERR_FILENO);
		ft_putstr_fd("[utility [argument ...]]", STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	ft_freetab(&opt->cpy);
	ft_freestr(&opt->path);
	ft_freestr(&opt->cmd);
	ft_freetab(&opt->ptr);
	ft_freetab(&opt->extra);
	return (1);
}
