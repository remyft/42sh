/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 21:57:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/24 02:34:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ENV_H
# define SHELL_ENV_H

typedef struct	s_shell_env
{
	int			ac;
	char		**av;
	char		*progpath;
	char		*progname;
	char		**env;
	int			ret;
	int			pid;
}				t_s_env;

void			init_shell_env(t_s_env *e, int ac, char **av, char **env);
void 			free_shell_env(t_s_env *e);

#endif
