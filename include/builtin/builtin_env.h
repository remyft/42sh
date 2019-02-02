/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:54:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/02 20:28:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ENV_H
# define BUILTIN_ENV_H

# include <sys/types.h>

/*
** Builtin errors
*/

enum
{
	ERR_OK = 0,
	ERR_MALLOC,
	ERR_ILLEGAL_OPT,
	ERR_NEED_ARG,
	ERR_NOT_FOUND,
	ERR_WRITE,
};

# define MALLOC_STR				"not enought memory"
# define ILLEGAL_OPTION_STR		"illegal option"
# define NEED_ARG_STR			"option requires an argument"
# define NOT_FOUND_STR			"No such file or directory"
# define WRITE_STR				"write error: Bad file descriptor"

/*
**Builtins options values
*/

enum
{
	BUILTIN_OPT_I = (1 << 1),
	BUILTIN_OPT_P = (1 << 2),
	BUILTIN_OPT_S = (1 << 3),
	BUILTIN_OPT_U = (1 << 4),
	BUILTIN_OPT_V = (1 << 5),
};

/*
** Main structure for env variables
*/

typedef struct	s_env_opt
{
	char		*cmdname;
	char		**env;
	int			options;
	int			verbosity;
	char		*path;
	char		*cmd;
}				t_e_opt;

typedef struct	s_opt
{
	char		value;
	int			(*handler)(size_t *, size_t *, char **, t_e_opt *);
}				t_opt;

# define ENV_OPTION_LESS		{ '-', env_opt_i }
# define ENV_OPTION_I			{ 'i', env_opt_i }
# define ENV_OPTION_V			{ 'v', env_opt_v }
# define ENV_OPTION_P			{ 'P', env_opt_p }
# define ENV_OPTION_U			{ 'u', env_opt_u }

void			env_free_opt(t_e_opt *opt);
int				env_options(size_t *i, size_t *j, char **cmd, t_e_opt *opt);
int				env_opt_i(size_t *i, size_t *j, char **cmd, t_e_opt *opt);
int				env_opt_v(size_t *i, size_t *j, char **cmd, t_e_opt *opt);
int				env_opt_p(size_t *i, size_t *j, char **cmd, t_e_opt *opt);
int				env_opt_u(size_t *i, size_t *j, char **cmd, t_e_opt *opt);
int				env_error(int err, char *c, t_e_opt *opt);

#endif
