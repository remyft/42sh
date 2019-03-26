/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:48:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/26 17:44:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "interactive_error.h"
#include "token.h"

static char		get_delimiter(int type)
{
	if (type == BACKSLASH)
		return ('\\');
	if (type == DOUBLE_QUOTE)
		return ('"');
	if (type == SINGLE_QUOTE)
		return ('\'');
	if (type == BRACE)
		return ('{');
	if (type == PARENTHESE)
		return (')');
	if (type == BACKQUOTE)
		return ('`');
	return ('?');
}

int				interactive_error(int err, char *delimiter, t_s_env *e)
{
	static char	*errors[] = {
		"command substitution: unexpected EOF while looking for matching",
		"warning: here-document delimited by end-of-file"
	};

	ft_dprintf(STDERR_FILENO, "%s: %s", e->progname, errors[err]);
	if (err < ERR_NON_INT_HDOC)
		ft_dprintf(STDERR_FILENO, " `%c'\n", get_delimiter(*delimiter));
	else
		ft_dprintf(STDERR_FILENO, " (wanted `%s')\n", delimiter);
	e->ret = 1;
	return (1);
}
