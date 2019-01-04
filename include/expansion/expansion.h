/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:20:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/04 02:44:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "shell_env.h"
# include "parser.h"

# define SEPARATORS		" \t\n"
# define RET_CHUNK		100

/*
** Structure for expansions values
*/
typedef struct	s_ret
{
	char		*word;
	size_t		w_len;
	size_t		w_max;
	int			brace;
	int			hash;
	char		*substitute;
	int			freeable;
	int			action;
}				t_ret;

/*
** Structure for expansions global variables
*/
typedef struct	s_expansion
{
	char		*ifs;
	t_s_env		*e;
	const char	*buff;
	size_t		buff_len;
	size_t		i;
	int			quoted;
}				t_exp;

int				expand(const char *buff, t_m_list *list, t_s_env *e);
int				expand_parameter(t_ret *ret, t_exp *param, int (*end)(t_exp *));
int				expand_error(int error, const char *progname, char *errmsg);

int				expand_dollar_do_expansion(t_ret *parameter);
int				expand_dollar_get_action(t_ret *parameter, t_exp *param);
int				expand_dollar_parameter(t_exp *param, t_ret *ret);
int				expand_dollar_parameter_value(t_ret *parameter, t_exp *param);
int				expand_dollar_special(t_ret *sub, t_ret *to, t_exp *param);
int				expand_dollar_subs(t_exp *param, t_ret *ret);
int				expand_dollar_word_value(t_ret *parameter, t_exp *param);
int				expand_dollar_word(t_ret *ret, t_exp *param, char op, char cl);

int				is_word_end(t_exp *param);
int				is_valid_name(int c);
int				is_special(int c);
int				is_expand_null(t_ret *ret);

int				param_addchar(char c, t_ret *ret);
int				param_addstr(const char *str, t_ret *ret);

void			expand_free_t_ret(t_ret *ret);

int				expand_arithmetic(t_exp *param, t_ret *ret);
int				expand_subshell(t_exp *param, t_ret *ret);

void			debug_expansion(char *name, t_ret *ret);

#endif
