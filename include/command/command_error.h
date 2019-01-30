/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:30:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/30 15:04:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_ERROR_H
# define COMMAND_ERROR_H

enum
{
	ERR_OK_VAL = 0,
	ERR_EXEC_VAL,
	ERR_MALLOC_VAL,
	ERR_NOT_FOUND_VAL,
	ERR_NO_SUCH_FILE_VAL,
	ERR_PERM_VAL,
	ERR_IS_DIRECTORY_VAL,
};

# define ERR_EXEC_STR			"execution failed"
# define ERR_MALLOC_STR			"not enought memory"
# define ERR_NOT_FOUND_STR		"command not found"
# define ERR_NO_SUCH_FILE_STR	"No such file or directory"
# define ERR_PERM_STR			"Permission denied"
# define ERR_IS_DIRECTORY_STR	"Is a directory"

#endif
