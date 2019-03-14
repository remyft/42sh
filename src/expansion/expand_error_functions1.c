/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error_functions1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:09:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/10 21:01:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "expansion.h"
#include "expansion_errors.h"

void			err_none_func(t_ret *ret, t_exp *par, t_s_env *e)
{
	(void)ret;
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", e->progname, ERR_NONE_STR);
}

void			err_syntax_func(t_ret *ret, t_exp *par, t_s_env *e)
{
	(void)ret;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", e->progname, par->buff,
		ERR_SYNTAX_STR);
}

void			err_modifier_func(t_ret *ret, t_exp *par, t_s_env *e)
{
	(void)ret;
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", e->progname, ERR_MODIFIER_STR);
}

void			err_unhandled_func(t_ret *ret, t_exp *par, t_s_env *e)
{
	ft_dprintf(STDERR_FILENO, "%s: `%s': %s %s\n", e->progname,
		par->buff, ret->word, ERR_UNHANDLED_STR);
}

void			err_malloc_func(t_ret *ret, t_exp *par, t_s_env *e)
{
	(void)ret;
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", e->progname, ERR_MALLOC_STR);
}
