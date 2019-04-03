/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:35:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/03 21:14:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERRORS_H
# define PARSER_ERRORS_H

# include "token.h"

enum
{
	ERR_FREE_ALL = -1,
	ERR_NONE,
	ERR_UNEXPECTED_TOKEN,
	ERR_MISSING_PARAMETER,
	ERR_NOT_HANDLED_YET,
	ERR_MALLOC_FAILED,
	ERR_TOKENIZATION,
	ERR_SIGNAL,
	ERR_MISSING_QUOTE
};

# define UNEXPECTED_STR	"syntax error near unexpected token"
# define PARAMETER_STR	"syntax error: missing token"
# define HANDLED_STR	"syntax error near unhandled token"
# define MALLOC_STR		"syntax error: malloc failed"
# define TOKENIZE_STR	"syntax error: tokenisation failed near"
# define SIGNAL_STR		"signal failed near"
# define QUOTE_STR		"unexpected EOF while looking for matching"

typedef struct	s_error
{
	const char	*str;
	void		(*handler)(const char *, t_token *, t_s_env *);
}				t_err;

void			default_err(const char *, t_token *, t_s_env *);
void			missing_quote_err(const char *, t_token *, t_s_env *);
void			eof_err(const char *, t_token *, t_s_env *);

#endif
