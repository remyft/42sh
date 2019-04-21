/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 05:56:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/21 16:34:37 by tsisadag         ###   ########.fr       */
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
# define BUILTIN_SOURCE		{ "source"  , builtin_source }
# define BUILTIN_UNALIAS	{ "unalias" , builtin_unalias }
# define BUILTIN_UNSETENV	{ "unsetenv", builtin_unsetenv }
# define BUILTIN_TYPE       { "type", builtin_type }
# define BUILTIN_EXPORT     { "export", builtin_export }
# define BUILTIN_SET        { "set", builtin_set }
# define BUILTIN_UNSET      { "unset", builtin_unset }

typedef struct	s_builtins
{
	char		*name;
	int			(*handler)(t_execute *, t_s_env *);
}				t_builtins;

typedef struct	s_errors
{
	char		*error;
	int			ret;
}				t_errors;

int				builtin_alias(t_execute *exec, t_s_env *e);
int				builtin_cd(t_execute *exec, t_s_env *e);
int				builtin_echo(t_execute *exec, t_s_env *e);
int				builtin_env(t_execute *exec, t_s_env *e);
int				builtin_exit(t_execute *exec, t_s_env *e);
int				builtin_setenv(t_execute *exec, t_s_env *e);
int				builtin_source(t_execute *exec, t_s_env *e);
int				builtin_unalias(t_execute *exec, t_s_env *e);
int				builtin_unsetenv(t_execute *exec, t_s_env *e);
int             builtin_type(t_execute *exec, t_s_env *e);
int             builtin_export(t_execute *exec, t_s_env *e);
int             builtin_set(t_execute *exec, t_s_env *e);
int             builtin_unset(t_execute *exec, t_s_env *e);

#endif
