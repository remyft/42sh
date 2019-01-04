/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 02:33:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/03 18:05:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_errors.h"

int				expand_error(int error, const char *progname, char *errmsg)
{
	static char	*err[] = {
		ERR_NONE_STR, ERR_SYNTAX_STR, ERR_MODIFIER_STR, ERR_UNHANDLED_YET_STR,
		ERR_MALLOC_STR, ERR_NO_ENV_VALUE_STR, ERR_DIRECTORY_STACK_STR,
		ERR_GIVEN_STR, ERR_NO_SUCH_USER_STR,
	};

	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(err[error], STDERR_FILENO);
	if (error >= ERR_GIVEN)
		ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}
