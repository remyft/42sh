/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error_functions2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:09:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/15 05:04:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "expansion.h"
#include "expansion_errors.h"

void			err_no_env_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", progname, ERR_NO_ENV_STR);
}

void			err_directory_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", progname, ERR_DIRECTORY_STACK_STR);
}

void			err_given_func(const char *progname, t_ret *ret)
{
	ft_dprintf(STDERR_FILENO, "%s: %s\n", progname, ret ? ret->word : "");
}

void			err_no_user_func(const char *progname, t_ret *ret)
{
	ft_dprintf(STDERR_FILENO, "%s: %s %s\n", progname, ERR_NO_SUCH_USER_STR,
		ret ? ret->word : "");
}

void			err_ambigous_func(const char *progname, t_ret *ret)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", progname,
		ret ? ret->substitute : "", ERR_AMBIGUOUS_STR);
}
