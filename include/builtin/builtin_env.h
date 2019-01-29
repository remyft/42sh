/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:54:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/29 13:33:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ENV_H
# define BUILTIN_ENV_H

# include <sys/types.h>

enum
{
	ERR_OK = 0,
	ERR_MALLOC,
	ERR_ILLEGAL_OPT,
	ERR_NEED_ARG,
	ERR_NOT_FOUND,
	ERR_WRITE,
};

# define MALLOC_STR			"not enought memory"
# define ILLEGAL_OPTION_STR	"illegal option"
# define NEED_ARG_STR		"option requires an argument"
# define NOT_FOUND_STR		"No such file or directory"
# define WRITE_STR			"write error: Bad file descriptor"

/*
** Main structure for env variables
*/

typedef struct	s_env_opt
{
	char		*cmdname;
	char		**env;
	int			i;
	int			v;
//	int			p;
	char		*path;
	int			freeable;
	char		*cmd;
	int			s;
	int			u;
//	char		**ptr;
	char		**extra;
}				t_e_opt;

typedef struct	s_opt
{
	char		value;
	int			(*handler)(size_t *, size_t *, char **, t_e_opt *);
}				t_opt;

# define ENV_OPTION_LESS		{ '-', builtin_env_opt_i }
# define ENV_OPTION_I			{ 'i', builtin_env_opt_i }
# define ENV_OPTION_V			{ 'v', builtin_env_opt_v }
# define ENV_OPTION_P			{ 'P', builtin_env_opt_p }
# define ENV_OPTION_U			{ 'u', builtin_env_opt_u }

void			builtin_env_free_opt(t_e_opt *opt);
int				builtin_env_options(size_t *i, size_t *j, char **cmd, t_e_opt *opt);
int				builtin_env_opt_i(size_t *i, size_t *j, char **cmd, t_e_opt *opt);
int				builtin_env_opt_v(size_t *i, size_t *j, char **cmd, t_e_opt *opt);
int				builtin_env_opt_p(size_t *i, size_t *j, char **cmd, t_e_opt *opt);
int				builtin_env_opt_u(size_t *i, size_t *j, char **cmd, t_e_opt *opt);
int				builtin_env_error(int err, char c, t_e_opt *opt);

#endif
