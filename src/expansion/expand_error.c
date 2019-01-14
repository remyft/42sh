/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 02:33:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/13 21:16:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

int				expand_error(int error, const char *progname, t_ret *ret)
{
	static char	*err[] = {
		ERR_NONE_STR, ERR_SYNTAX_STR, ERR_MODIFIER_STR, ERR_UNHANDLED_YET_STR,
		ERR_MALLOC_STR, ERR_NO_ENV_VALUE_STR, ERR_DIRECTORY_STACK_STR,
		ERR_GIVEN_STR, ERR_NO_SUCH_USER_STR,
	};

	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(err[error], STDERR_FILENO);
	if (error >= ERR_GIVEN && ret)
		ft_putstr_fd(ret->word, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (ret)
		free_t_ret(&ret);
	return (1);
}
