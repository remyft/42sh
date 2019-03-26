/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_error.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:49:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/26 17:18:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTIVE_ERROR_H
# define INTERACTIVE_ERROR_H

# include "shell_env.h"

enum
{
	ERR_NON_INT_SUBST = 0,
	ERR_NON_INT_HDOC
};

int				interactive_error(int err, char *delimiter, t_s_env *e);

#endif
