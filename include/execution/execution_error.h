/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:30:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/22 02:34:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_ERROR_H
# define EXECUTION_ERROR_H

enum
{
	ERR_OK_VAL = 0,
	ERR_MALLOC_VAL,
	ERR_NOT_FOUND_VAL,
	ERR_PERM_VAL,
};

# define ERR_MALLOC_FUNC		"not enought memory"
# define ERR_NOT_FOUND_FUNC		"command not found"
# define ERR_PERM_FUNC			"Permission denied"

#endif
