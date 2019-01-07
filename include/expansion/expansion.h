/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:20:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/07 00:19:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "shell_env.h"
# include "parser.h"

# define RET_CHUNK		100

/*
** Structure for expansions values
*/
# define NULLRET		(t_ret *)0

typedef struct	s_ret
{
	char			*word;
	size_t			w_len;
	size_t			w_max;
	int				brace;
	int				hash;
	char			*substitute;
	int				freeable;
	int				action;
	struct s_ret	*next;
}				t_ret;

/*
** Structure for expansions global variables
*/
typedef struct	s_expansion
{
	t_s_env		*e;
	const char	*buff;
	size_t		buff_len;
	size_t		i;
	int			quoted;
	int			expand;
}				t_exp;

int				expand(const char *buff, t_m_list *list, t_s_env *e);
int				expand_loop(t_ret *ret, t_exp *param, int (*end_loop)(t_exp *));
int				expand_error(int error, const char *progname, char *errmsg);
int				expand_end(t_ret *ret, t_argument *arg);

int				expand_fieldsplit(t_ret **ret, const char *ifs);
void			quote_removal(t_ret *ret);

int				param_addchar(char c, t_ret *ret);
int				param_addstr(const char *str, t_ret *ret);

void			expand_free_t_ret(t_ret *ret);
void			free_t_ret(t_ret **ret);

int				expand_arithmetic(t_exp *param, t_ret *ret);
int				expand_subshell(t_exp *param, t_ret *ret);

void			debug_expansion(char *name, t_ret *ret);

#endif
