/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:35:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/12 19:05:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERRORS_H
# define PARSER_ERRORS_H

enum
{
	ERR_NONE,
	ERR_UNEXPECTED_TOKEN,
	ERR_MISSING_PARAMETER,
	ERR_NOT_HANDLED_YET,
	ERR_MALLOC_FAILED,
	ERR_TOKENIZATION,
};

# define NONE_STR				NULL
# define UNEXPECTED_TOKEN_STR	"parse error near unexpected token"
# define MISSING_PARAMETER_STR	"parse error: missing token"
# define NOT_HANDLED_YET_STR	"parse error near unhandled token"
# define MALLOC_FAILED_STR		"parse error: malloc failed"
# define TOKENIZATION_STR		"parse error: tokenisation failed"

#endif
