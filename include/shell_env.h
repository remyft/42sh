/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 21:57:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/03 09:22:06 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ENV_H
# define SHELL_ENV_H

# include <term.h>
# define IFS_SEPARATORS		" \t\n"

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
	char				*cmd;
	struct s_process	*next;
}				t_process;


typedef struct	s_jobs
{
	int					id;
	int					pgid;
	t_process			*process;
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
	int				ret;
	int				pid;
	struct termios	save;
	int				shell_loop;
	int				forked;
}				t_s_env;

void			init_shell_env(t_s_env *e, int ac, char **av, char **env);
void			free_shell_env(t_s_env *e);
void			launch_new_cmd(char **line, t_s_env *e);

#endif
