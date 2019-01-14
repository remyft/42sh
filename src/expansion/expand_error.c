/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 02:33:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/14 22:10:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_errors.h"

int				expand_error(int error, const char *progname, t_ret *ret)
{
	static t_error	err[] = {
		ERR_NONE_FUNC, ERR_SYNTAX_FUNC, ERR_MODIFIER_FUNC, ERR_UNHANDLED_FUNC,
		ERR_MALLOC_FUNC, ERR_NO_ENV_FUNC, ERR_DIRECTORY_STACK_FUNC,
		ERR_GIVEN_FUNC, ERR_NO_SUCH_USER_FUNC, ERR_AMBIGUOUS_FUNC,
	};
	size_t			i;

	i = 0;
	while (i < sizeof(err) / sizeof(err[0]))
	{
		if (error == err[i].error)
			return (err[i].handler(progname, ret));
		i++;
	}
	return (1);
}
