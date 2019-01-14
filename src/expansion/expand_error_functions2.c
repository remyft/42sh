/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error_functions2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:09:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/14 22:10:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

int				err_no_env_func(const char *progname, t_ret *ret)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_NO_ENV_STR, STDERR_FILENO);
	if (ret)
		free_t_ret(&ret);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

int				err_directory_func(const char *progname, t_ret *ret)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_DIRECTORY_STACK_STR, STDERR_FILENO);
	if (ret)
		free_t_ret(&ret);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

int				err_given_func(const char *progname, t_ret *ret)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (ret)
	{
		ft_putstr_fd(ret->word, STDERR_FILENO);
		free_t_ret(&ret);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

int				err_no_user_func(const char *progname, t_ret *ret)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_NO_SUCH_USER_STR, STDERR_FILENO);
	if (ret)
	{
		ft_putstr_fd(ret->word, STDERR_FILENO);
		free_t_ret(&ret);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

int				err_ambigous_func(const char *progname, t_ret *ret)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (ret)
	{
		ft_putstr_fd(ret->substitute, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(ERR_AMBIGUOUS_STR, STDERR_FILENO);
		free_t_ret(&ret);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}
