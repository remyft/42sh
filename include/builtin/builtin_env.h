/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:54:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 20:30:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ENV_H
# define BUILTIN_ENV_H

enum
{
	ERR_OK = 0,
	ERR_MALLOC,
	ERR_ILLEGAL_OPT,
	ERR_NEED_ARG,
};

# define MALLOC_STR			"not enought memory"
# define ILLEGAL_OPTION_STR	"illegal option"
# define NEED_ARG_STR		"option requires an argument"
# define NO_SUCH_FILE_STR	"no such file or directory"

typedef struct	s_env_opt
{
	char		*cmdname;
	char		**cpy;
	int			i;
	int			v;
	int			p;
	char		*path;
	char		*cmd;
	int			s;
	int			u;
	char		**ptr;
	char		**extra;
}				t_e_opt;

int				builtin_env_check(int *i, int *j, char **cmd, t_e_opt *opt);

#endif
