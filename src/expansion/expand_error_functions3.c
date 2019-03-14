/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error_functions3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:26:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/14 17:07:26 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "expansion.h"
#include "expansion_errors.h"

void			err_pipe_func(t_ret *ret, t_exp *par, t_s_env *e)
{
	(void)ret;
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", e->progname, ERR_PIPE_STR);
}

void			err_fcntl_func(t_ret *ret, t_exp *par, t_s_env *e)
{
	(void)ret;
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", e->progname, ERR_FCNTL_STR);
}

void			err_fork_func(t_ret *ret, t_exp *par, t_s_env *e)
{
	(void)ret;
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", e->progname, ERR_FORK_STR);
}

void			err_no_match_func(t_ret *ret, t_exp *par, t_s_env *e)
{
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", e->progname,
			ERR_NO_MATCH_FOUND_STR, ret->word);
}
