/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error_functions2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:09:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/16 00:52:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

void			err_no_env_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_NO_ENV_STR, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void			err_directory_func(const char *progname, t_ret *ret)
{
	(void)ret;
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_DIRECTORY_STACK_STR, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void			err_given_func(const char *progname, t_ret *ret)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (ret)
		ft_putstr_fd(ret->word, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void			err_no_user_func(const char *progname, t_ret *ret)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_NO_SUCH_USER_STR, STDERR_FILENO);
	if (ret)
		ft_putstr_fd(ret->word, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void			err_ambigous_func(const char *progname, t_ret *ret)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (ret)
	{
		ft_putstr_fd(ret->substitute, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(ERR_AMBIGUOUS_STR, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}
