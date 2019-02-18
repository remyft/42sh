/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 05:56:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/15 22:04:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "command.h"
# include "shell_env.h"

# define BUILTIN_ALIAS		{ "alias"   , builtin_alias }
# define BUILTIN_CD			{ "cd"      , builtin_cd }
# define BUILTIN_ECHO		{ "echo"    , builtin_echo }
# define BUILTIN_ENV		{ "env"     , builtin_env }
# define BUILTIN_EXIT		{ "exit"    , builtin_exit }
# define BUILTIN_SETENV		{ "setenv"  , builtin_setenv }
# define BUILTIN_UNSETENV	{ "unsetenv", builtin_unsetenv }

typedef struct	s_builtins
{
	char		*name;
	int			(*handler)(t_execute *, t_s_env *);
}				t_builtins;

int				builtin_alias(t_execute *exec, t_s_env *e);
int				builtin_cd(t_execute *exec, t_s_env *e);
int				builtin_echo(t_execute *exec, t_s_env *e);
int				builtin_env(t_execute *exec, t_s_env *e);
int				builtin_exit(t_execute *exec, t_s_env *e);
int				builtin_setenv(t_execute *exec, t_s_env *e);
int				builtin_unsetenv(t_execute *exec, t_s_env *e);

#endif
