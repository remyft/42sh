/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:30:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/21 19:45:37 by gbourgeo         ###   ########.fr       */
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
# define ERR_NOT_FOUND_FUNC		"No such file or directory"
# define ERR_PERM_FUNC			"Permission denied"

#endif
