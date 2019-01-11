/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 02:17:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/11 05:01:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"
# include "shell_env.h"

int				execute(const char *buff, t_m_list *list, t_s_env *e);

void			debug_execution(t_command *cmd);

#endif
