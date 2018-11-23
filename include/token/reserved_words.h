/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserved_words.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:43:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/22 22:47:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESERVED_WORDS_H
# define RESERVED_WORDS_H

# define IF		{ "if",    (1 << 0)}
# define THEN	{ "then",  (1 << 1)}
# define ELSE	{ "else",  (1 << 2)}
# define ELIF	{ "elif",  (1 << 3)}
# define FI		{ "fi",    (1 << 4)}
# define DO		{ "do",    (1 << 5)}
# define DONE	{ "done",  (1 << 6)}
# define CASE	{ "case",  (1 << 7)}
# define ESAC	{ "esac",  (1 << 8)}
# define WHILE	{ "while", (1 << 9)}
# define UNTIL	{ "until", (1 << 10)}
# define FOR	{ "for",   (1 << 11)}

#endif
