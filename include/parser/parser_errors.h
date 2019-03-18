/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:35:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/16 18:01:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERRORS_H
# define PARSER_ERRORS_H

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
};

# define NONE_STR				NULL
# define UNEXPECTED_TOKEN_STR	"syntax error near unexpected token"
# define MISSING_PARAMETER_STR	"syntax error: missing token"
# define NOT_HANDLED_YET_STR	"syntax error near unhandled token"
# define MALLOC_FAILED_STR		"syntax error: malloc failed"
# define TOKENIZATION_STR		"syntax error: tokenisation failed near"
# define SIGNAL_STR				"signal failed near"

#endif
