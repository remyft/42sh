/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 05:56:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/25 10:24:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define BUILTIN_ECHO		{ "echo"    , builtin_echo }
# define BUILTIN_CD			{ "cd"      , builtin_cd }
# define BUILTIN_SETENV		{ "setenv"  , builtin_setenv }
# define BUILTIN_UNSETENV	{ "unsetenv", builtin_unsetenv }
# define BUILTIN_ENV		{ "env"     , builtin_env }
# define BUILTIN_EXIT		{ "exit"    , builtin_exit }

typedef struct	s_builtins
{
	char		*name;
	int			(*handler)(char **args, t_s_env *e);
}				t_builtins;

int				builtin_echo(char **args, t_s_env *e);
int				builtin_cd(char **args, t_s_env *e);
int				builtin_setenv(char **args, t_s_env *e);
int				builtin_unsetenv(char **args, t_s_env *e);
int				builtin_env(char **args, t_s_env *e);
int				builtin_exit(char **args, t_s_env *e);

#endif
