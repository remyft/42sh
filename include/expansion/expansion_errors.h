/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_errors.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 17:39:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/03 20:20:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_ERRORS_H
# define EXPANSION_ERRORS_H

# define ERR_NONE_STR				"? ? ?"
# define ERR_SYNTAX_STR				"bad substitution."
# define ERR_MODIFIER_STR			"unrecognized modifier."
# define ERR_UNHANDLED_YET_STR		"pattern not handled."
# define ERR_MALLOC_STR				"malloc error."
# define ERR_NO_ENV_VALUE_STR		"variable not set."
# define ERR_DIRECTORY_STACK_STR	"not enough directory stack entries."
# define ERR_GIVEN_STR				""
# define ERR_NO_SUCH_USER_STR		"no such user or named directory: "

/*
** Enumeration of expansions errors
*/
enum
{
	ERR_NONE = 0,
	ERR_SYNTAX,
	ERR_MODIFIER,
	ERR_UNHANDLED_YET,
	ERR_MALLOC,
	ERR_NO_ENV_VALUE,
	ERR_DIRECTORY_STACK,
	ERR_GIVEN,
	ERR_NO_SUCH_USER,
};

#endif
