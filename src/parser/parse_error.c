/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:11:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/23 11:00:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parser.h"
#include "ft_dprintf.h"

int				parse_error(int err, t_token *token, t_s_env *e)
{
	static char	*errors[] = {
		"parse error near unexpected token",
		"parse error: missing token",
		"parse error near unhandled token",
		"parse error: malloc failed",
	};

	ft_dprintf(STDERR_FILENO, "%s: %s `", e->progname, errors[err]);
	if (token == NULLTOKEN)
		write(STDERR_FILENO, "\\n", 2);
	else
		write(STDERR_FILENO, token->head, token->len);
	ft_dprintf(STDERR_FILENO, "'\n");
	e->ret = 2;
	return (0);
}
