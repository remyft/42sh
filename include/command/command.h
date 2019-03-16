/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 02:17:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/10 19:08:25 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "parser.h"
# include "shell_env.h"

# define NULLPID	(t_pid *)0

typedef struct	s_execute
{
	t_argument		*variable;
	t_argument		*command;
	t_redirection	*redirection;
	char			**cmd;
	char			**env;
	int				builtin;
	int				async;
	int				job_id;
	int				fds[3];
}				t_execute;

typedef int		(*t_builtin)(t_execute *, t_s_env *);

int				execute_list(t_m_list *list, t_s_env *e);
int				command_access(char *path, char *absolute_path);
int				command_builtin(t_builtin builtin, t_execute *exec, t_s_env *e);
int				command_check(t_jobs *job, t_process *p, t_s_env *e);
int				command_job(t_jobs *job, t_s_env *e);
int				command_error(char *progname, int err, char **cmd, t_s_env *e);
void			command_execute(t_execute *exec, t_s_env *e);
void			command_free(t_execute *exec, char *name);
char			**command_group_command(t_argument *cmd);
char			**command_group_env(t_argument *var, t_argument *cmd,
				const char **public, const char **private);
int				command_path(char **path, char *cmd, char *paths);
int				command_parse(void *cmd, t_s_env *e);
int				command_pipe(void *cmd, t_s_env *e, int ppfd[2]);
int				command_prepare(t_execute *exec, t_s_env *e);
int				command_redirect(int fds[3], t_redirection *redir, t_s_env *e);
int				command_restore_fds(int fds[3]);
int				command_save_fds(int fd, int fds[3]);
void			command_wait2(pid_t pid, t_execute *exec, t_s_env *e);
int				command_system(t_jobs *job, t_process *p, t_s_env *e);
void			command_wait(pid_t pid, int async, int *ret);

void			quote_removal(t_argument *arg);
void			variable_assignment(t_command *cmd, t_s_env *e);

char			**modify_environ(t_argument *var, t_execute *exec);

int				isvalidname(char *str, size_t n);
t_jobs			*jobs_prepare(t_s_env *e);

void			command_debug(t_command *cmd);

#endif
