/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_source.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:18:49 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/18 21:43:35 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_SOURCE_H
# define BUILTIN_SOURCE_H

# include "shell_env.h"

enum
{
	ERR_OK,
	ERR_IS_DIR,
	ERR_NOT_ARG,
	ERR_NO_SUCH_FILE,
	ERR_PERMISSION,
	ERR_MALLOC,
	ERR_NOT_FOUND,
};

#endif
