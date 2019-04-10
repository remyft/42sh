/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 21:57:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/10 16:59:16 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ENV_H
# define SHELL_ENV_H

# include <term.h>

# define IFS_DEFAULT	" \t\n"

# define NULLALIAS		(t_alias *)0

typedef struct	s_alias
{
	char			*key;
	char			*value;
	int				in_use;
	struct s_alias	*next;
	struct s_alias	*prev;
}				t_alias;


typedef struct	s_process
{
	int					pid;
	int					status;
	int					s_suspended;
	int					s_signal;
	int					exit_status;
	int					forked;
	int					type;
	int					pipe[2];
	int					fds[3];
	void				*exec;
	struct s_process	*next;
}				t_process;

typedef struct	s_m_process
{
	int					ret;
	int					type;
	int					m_pgid;
	struct s_process	*p;
	struct s_m_process	*next;
}				t_m_process;


typedef struct	s_jobs
{
	int					id;
	int					pgid;
	int					foreground;
	int					status;
	char				*cmd_name;
	t_m_process			*m_process;
	t_m_process			*curr;
	struct s_jobs		*prev;
	struct s_jobs		*next;
}				t_jobs;

typedef struct	s_shell_env
{
	int				ac;
	char			**av;
	char			*progpath;
	char			*progname;
	char			**public_env;
	char			**private_env;
	t_alias			*alias_list;
	t_jobs			*jobs;
	int				job_id;
	int				ret;
	int				interactive;
	int				fd;
	int				pid;
	int				pgid;
	struct termios	save;
	int				shell_loop;
	int				forked;
}				t_s_env;

void			init_shell_env(t_s_env *e, int ac, char **av, char **env);
void			free_shell_env(t_s_env *e);
void			launch_new_cmd(char **line, t_s_env *e);

#endif
