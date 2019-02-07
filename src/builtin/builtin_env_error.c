/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 19:36:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/07 22:49:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "builtin_env.h"

int				env_error(int err, char *c, t_e_opt *opt)
{
	static char	*errors[] = {
		"", MALLOC_STR, ILLEGAL_OPTION_STR, NEED_ARG_STR, NOT_FOUND_STR,
		WRITE_STR,
	};
	static int	values[] = {
		1, 1, 1, 1, 127, 1,
	};

	ft_dprintf(STDERR_FILENO, "%s: %s", opt->cmdname, errors[err]);
	if (err == ERR_ILLEGAL_OPT || err == ERR_NEED_ARG)
	{
		ft_dprintf(STDERR_FILENO, " -- %c\nusage: %s ", *c, opt->cmdname);
		ft_dprintf(STDERR_FILENO, "[-iv] [-P utilpath] [-u name]\n\t");
		ft_dprintf(STDERR_FILENO, "[name=value ...] [utility [args ...]]\n");
	}
	else
		ft_dprintf(STDERR_FILENO, ": %s\n", c);
	env_free_opt(opt);
	return (values[err]);
}
