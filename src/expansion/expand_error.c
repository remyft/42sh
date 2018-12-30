/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 02:33:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/30 10:47:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

int				expand_error(int error, const char *progname, char *errmsg)
{
	static char	*err[] = {
		"no error, what's up ?", "bad substitution", "unrecognized modifier",
		"pattern not handled yet", "malloc error",
	};

	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (error < ERR_GIVEN)
		ft_putendl_fd(err[error], STDERR_FILENO);
	else
		ft_putendl_fd(errmsg, STDERR_FILENO);
	return (1);
}
