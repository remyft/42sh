/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_action.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 05:45:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/30 19:46:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_ACTION_H
# define EXPANSION_ACTION_H

/*
** Actions to be performed on ${} expansion with the characters:
**
** NO_ACTION						None
** COLON_ACTION						:
** ACT_NULL_SUBST					-
** ACT_NULL_ASSIGN					=
** ACT_NULL_ERROR					?
** ACT_NONNULL_SUBST				+
** REMOVE_SMALLEST_SUFFIX_PATTERN	%
** REMOVE_LARGEST_SUFFIX_PATTERN	%%
** REMOVE_SMALLEST_PREFIX_PATTERN	#
** REMOVE_LARGEST_PREFIX_PATTERN	##
*/
# define ACTIONS_VALUES		"-=?+"

enum
{
	NO_ACTION = 0,
	COLON_ACTION = (1 << 0),
	ACT_NULL_SUBST = (1 << 1),
	ACT_NULL_ASSIGN = (1 << 2),
	ACT_NULL_ERROR = (1 << 3),
	ACT_NONNULL_SUBST = (1 << 4),
	REMOVE_SMALLEST_SUFFIX_PATTERN = (1 << 5),
	REMOVE_LARGEST_SUFFIX_PATTERN = (1 << 6),
	REMOVE_SMALLEST_PREFIX_PATTERN = (1 << 7),
	REMOVE_LARGEST_PREFIX_PATTERN = (1 << 8),
};

#endif
