/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error_functions1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:09:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/15 05:07:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "expansion.h"
#include "expansion_errors.h"

void			err_none_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", progname, ERR_NONE_STR);
}

void			err_syntax_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", progname, ERR_SYNTAX_STR);
}

void			err_modifier_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", progname, ERR_MODIFIER_STR);
}

void			err_unhandled_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", progname,
		ret ? ret->word : "", ERR_UNHANDLED_STR);
}

void			err_malloc_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", progname, ERR_MALLOC_STR);
}
