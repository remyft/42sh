/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 02:33:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/13 18:22:55 by rfontain         ###   ########.fr       */
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
		ERR_PIPE_FUNC, ERR_FCNTL_FUNC, ERR_FORK_FUNC, ERR_NO_MATCH_FUNC,
	};
	size_t			i;

	i = 0;
	while (i < sizeof(err) / sizeof(err[0]) && error != err[i].error)
		i++;
	if (error == err[i].error)
		err[i].handler(progname, ret);
	expand_free_t_ret(ret, 0);
	return (1);
}
