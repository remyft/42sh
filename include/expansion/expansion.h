/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:20:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/30 19:44:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "shell_env.h"
# include "parser.h"

# define SEPARATORS		" \t\n"
# define RET_CHUNK		100

/*
** Enumeration of expansions errors
*/
enum
{
	ERR_NONE = 0,
	ERR_SYNTAX,
	ERR_MODIFIER,
	ERR_UNHANDLED_YET,
	ERR_MALLOC,
	ERR_GIVEN,
};

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
	int			tabval; // for debug
}				t_exp;

// typedef struct	s_expansion_handler
// {
// 	char		c;
// 	int			(*handler)(t_exp *);
// }				t_e_handler;

// # define OP_EXP_BACKSLSH	{ '\\', expand_backslash }
// # define OP_EXP_DOLLAR		{ '$',  expand_dollar }
// # define OP_EXP_BACKTICK	{ '`',  expand_backtick }
// # define OP_EXP_DQUOTE		{ '"',  expand_dquote }
// # define OP_EXP_SQUOTE		{ '\'', expand_squote }
// # define OP_EXP_TILDE		{ '~',  expand_tilde }
// # define OP_EXP_STAR		{ '*',  expand_glob }
// # define OP_EXP_BRACKET		{ '[',  expand_glob }
// # define OP_EXP_QUESTION	{ '?',  expand_glob }

int				expand(const char *buff, t_m_list *list, t_s_env *e);
int				expand_mword(t_ret *ret, t_exp *param, int (*end)(t_exp *));
int				expand_error(int error, const char *progname, char *errmsg);

int				expand_backslash(t_exp *param, t_ret *ret);
int				expand_dollar(t_exp *param, t_ret *ret);
int				expand_backtick(t_exp *param, t_ret *ret);
int				expand_dquote(t_exp *param, t_ret *ret);
int				expand_squote(t_exp *param, t_ret *ret);
int				expand_tilde(t_exp *param, t_ret *ret);
int				expand_glob(t_exp *param, t_ret *ret);

int				expand_dollar_parameter(t_exp *param, t_ret *ret);
int				expand_dollar_parameter_value(t_ret *parameter, t_exp *param);
int				expand_dollar_get_action(t_ret *parameter, t_exp *param);
int				expand_dollar_do_expansion(t_ret *parameter);
int				expand_dollar_word_value(t_ret *parameter, t_exp *param);
int				expand_dollar_subs(t_exp *param, t_ret *ret);
int				expand_dollar_word(t_ret *ret, t_exp *param, char op, char cl);

int				is_word_end(t_exp *param);
int				is_valid_name(int c);
int				is_special(int c);
int				is_expand_null(t_ret *ret);

int				param_addchar(char c, t_ret *ret);
int				param_addstr(char *str, t_ret *ret);

void			expand_free_t_ret(t_ret *ret);

int				exp_strncmp(const char *s1, const char *s2, unsigned int n);

void			debug_expansion(char *name, t_ret *ret, t_exp *param);

#endif
