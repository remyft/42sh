/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserved_words.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:43:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/10 23:09:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESERVED_WORDS_H
# define RESERVED_WORDS_H

/*
** Identifiers for token RESERVED_WORD
*/

enum
{
	IF_VALUE = 1,
	THEN_VALUE,
	ELSE_VALUE,
	ELIF_VALUE,
	FI_VALUE,
	DO_VALUE,
	DONE_VALUE,
	CASE_VALUE,
	ESAC_VALUE,
	WHILE_VALUE = 10,
	UNTIL_VALUE,
	FOR_VALUE,
};

# define IF		"if"
# define THEN	"then"
# define ELSE	"else"
# define ELIF	"elif"
# define FI		"fi"
# define DO		"do"
# define DONE	"done"
# define CASE	"case"
# define ESAC	"esac"
# define WHILE	"while"
# define UNTIL	"until"
# define FOR	"for"

# define TOKEN_IF		{ IF,    IF_VALUE }
# define TOKEN_THEN		{ THEN,  THEN_VALUE }
# define TOKEN_ELSE		{ ELSE,  ELSE_VALUE }
# define TOKEN_ELIF		{ ELIF,  ELIF_VALUE }
# define TOKEN_FI		{ FI,    FI_VALUE }
# define TOKEN_DO		{ DO,    DO_VALUE }
# define TOKEN_DONE		{ DONE,  DONE_VALUE }
# define TOKEN_CASE		{ CASE,  CASE_VALUE }
# define TOKEN_ESAC		{ ESAC,  ESAC_VALUE }
# define TOKEN_WHILE	{ WHILE, WHILE_VALUE }
# define TOKEN_UNTIL	{ UNTIL, UNTIL_VALUE }
# define TOKEN_FOR		{ FOR,   FOR_VALUE }

#endif
