/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 02:17:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/23 03:10:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"
# include "shell_env.h"

typedef struct	s_execute
{
	t_argument		*variable;
	t_argument		*command;
	t_redirection	*redirection;
	int				piped;
}				t_execute;

int				execute_list(t_m_list *list, t_s_env *e);
void			quote_removal(t_argument *arg);
void			variable_assignment(t_command *cmd, t_s_env *e);
int				parse_command(void *cmd, t_s_env *e);
int				fork_command(t_execute *exec, t_s_env *e);
void			execute_command(t_execute *exec, t_s_env *e);
char			**duplicate_environ(char **table);
char			**modify_environ(t_argument *var, t_argument *end, char **env);
char			**group_command(t_argument *cmd);
int				path_command(char **path, char *cmd, char *paths);
int				access_command(char *path);

int				isvalidname(char *str, size_t n);

void			debug_execution(t_command *cmd);

#endif
