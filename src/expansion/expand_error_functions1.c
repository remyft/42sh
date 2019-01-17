/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error_functions1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:09:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/16 00:51:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

void			err_none_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_NONE_STR, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void			err_syntax_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_SYNTAX_STR, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void			err_modifier_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_MODIFIER_STR, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void			err_unhandled_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_UNHANDLED_STR, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void			err_malloc_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_MALLOC_STR, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
