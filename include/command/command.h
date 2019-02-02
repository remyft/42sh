/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 02:17:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/31 23:16:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "parser.h"
# include "shell_env.h"

typedef struct	s_execute
{
	t_argument		*variable;
	t_argument		*command;
	t_redirection	*redirection;
	int				piped;
	char			**cmd;
	char			**env;
	int				builtin;
}				t_execute;

int				execute_list(t_m_list *list, t_s_env *e);
void			command_execute(t_execute *exec, t_s_env *e);
int				command_parse(void *cmd, t_s_env *e);
int				command_error(char *progname, int err, char **cmd);
void			command_free(t_execute *exec, char **public, char *name);

void			quote_removal(t_argument *arg);
void			variable_assignment(t_command *cmd, t_s_env *e);

int				command_prepare(t_execute *exec, t_s_env *e);
char			**command_group(t_argument *cmd);
int				command_check(t_execute *exec, t_s_env *e);
int				command_builtin(int (*builtin)(t_execute *, t_s_env *),
t_execute *exec, t_s_env *e);
int				command_fork(t_execute *exec, t_s_env *e);
int				command_path(char **path, char *cmd, char *paths);
int				command_access(char *path, int absolute_path);
int				command_redirect(t_redirection *redirection, t_s_env *e);

char			**modify_environ(t_argument *var, t_execute *exec);

int				isvalidname(char *str, size_t n);

void			debug_execution(t_command *cmd);

#endif
