/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 02:17:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/14 00:22:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"
# include "shell_env.h"

typedef struct	s_execute
{
	char		**var_assign;
	char		**args;
	char		**env;
}				t_execute;

int				execute(const char *buff, t_m_list *list, t_s_env *e);
int				group_var_and_command(t_argument *arg);
void			quote_removal(t_argument *arg);
void			variable_assignment(t_command *cmd, t_s_env *e);
int				exec_command(const char *buff, t_command *cmd, t_s_env *e);

int				isvalidname(char *str, size_t n);

void			debug_execution(t_command *cmd);

#endif
