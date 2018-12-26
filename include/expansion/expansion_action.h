/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_action.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 05:45:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/26 06:02:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_ACTION_H
# define EXPANSION_ACTION_H

# define ACTIONS_VALUES		"-=?+"

enum
{
	NO_ACTION = 0,
	COLON_ACTION = (1 << 0),
	SUBSTITUTE_1,
	REMOVE_SMALLEST_SUFFIX_PATTERN,
	REMOVE_LARGEST_SUFFIX_PATTERN,
	REMOVE_SMALLEST_PREFIX_PATTERN,
	REMOVE_LARGEST_PREFIX_PATTERN,
};

#endif
