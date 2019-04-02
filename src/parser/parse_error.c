/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:11:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/02 18:19:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "parser.h"
#include "parser_errors.h"
#include "token.h"

int				parse_error(int err, t_token *token, t_s_env *e)
{
	static char	*errors[] = {
		NONE_STR,
		UNEXPECTED_TOKEN_STR,
		MISSING_PARAMETER_STR,
		NOT_HANDLED_YET_STR,
		MALLOC_FAILED_STR,
		TOKENIZATION_STR,
		SIGNAL_STR,
	};

	e->ret = 130;
	if (err == ERR_FREE_ALL)
		return (0);
	ft_dprintf(STDERR_FILENO, "%s: %s `", e->progname, errors[err]);
	if (token == NULLTOKEN || *token->head == '\n')
		write(STDERR_FILENO, "\\n", 2);
	else
		write(STDERR_FILENO, token->head, token->len);
	ft_dprintf(STDERR_FILENO, "'\n");
	e->ret = 2;
	return (0);
}
