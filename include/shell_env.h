/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 21:57:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/07 00:52:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ENV_H
# define SHELL_ENV_H

# include <term.h>

# define IFS_SEPARATORS		" \t\n"

typedef struct	s_shell_env
{
	int				ac;
	char			**av;
	char			*progpath;
	char			*progname;
	char			**public_env;
	char			**private_env;
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
