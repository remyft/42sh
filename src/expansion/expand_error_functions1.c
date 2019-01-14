/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error_functions1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:09:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/14 22:10:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

int				err_none_func(const char *progname, t_ret *ret)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_NONE_STR, STDERR_FILENO);
	if (ret)
		free_t_ret(&ret);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

int				err_syntax_func(const char *progname, t_ret *ret)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_SYNTAX_STR, STDERR_FILENO);
	if (ret)
		free_t_ret(&ret);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

int				err_modifier_func(const char *progname, t_ret *ret)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_MODIFIER_STR, STDERR_FILENO);
	if (ret)
		free_t_ret(&ret);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

int				err_unhandled_func(const char *progname, t_ret *ret)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_UNHANDLED_STR, STDERR_FILENO);
	if (ret)
		free_t_ret(&ret);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

int				err_malloc_func(const char *progname, t_ret *ret)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_MALLOC_STR, STDERR_FILENO);
	if (ret)
		free_t_ret(&ret);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}
