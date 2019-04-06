/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:11:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/06 18:10:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "parser.h"
#include "parser_errors.h"
#include "token.h"

void			default_err(const char *err, t_token *token, t_s_env *e)
{
	ft_dprintf(STDERR_FILENO, "%s: %s `", e->progname, err);
	if (token == NULLTOKEN || *token->head == '\n')
		write(STDERR_FILENO, "\\n", 2);
	else
		write(STDERR_FILENO, token->head, token->len);
	ft_dprintf(STDERR_FILENO, "'\n");
}

static char		get_delimiter(int type)
{
	if (type == BACKSLASH)
		return ('\\');
	if (type == DOUBLE_QUOTE)
		return ('"');
	if (type == SINGLE_QUOTE)
		return ('\'');
	if (type == BRACE || type == D_BRACE)
		return ('}');
	if (type == PARENTHESE || type == D_PARENTHESE)
		return (')');
	if (type == BACKQUOTE)
		return ('`');
	return ('?');
}

void			missing_quote_err(const char *err, t_token *token, t_s_env *e)
{
	ft_dprintf(STDERR_FILENO, "%s: %s `%c'\n", e->progname, err,
	get_delimiter(quote_type(token->quote)));
}

int				parse_error(int err, t_token *token, t_s_env *e)
{
	static t_err	errors[] = {
		{ NULL, NULL },
		{ UNEXPECTED_STR, default_err },
		{ PARAMETER_STR, default_err },
		{ HANDLED_STR, default_err },
		{ MALLOC_STR, default_err },
		{ TOKENIZE_STR, default_err },
		{ SIGNAL_STR, default_err },
		{ QUOTE_STR, missing_quote_err },
	};

	e->ret = 130;
	if (err == ERR_FREE_ALL)
		return (0);
	errors[err].handler(errors[err].str, token, e);
	e->ret = 2;
	return (0);
}
