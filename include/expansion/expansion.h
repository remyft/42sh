/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:20:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/26 11:01:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

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
	ERR_MALLOC,
};

enum
{
	EXP_NOQUOTE,
	EXP_SQUOTE,
	EXP_DQUOTE,
	EXP_DOLLAR,
	EXP_BRACKET,
};

typedef struct	s_ret
{
	int			quoted;
	char		*word;
	size_t		w_len;
	size_t		w_max;
}				t_ret;

typedef struct	s_expansion
{
	char		*ifs;
	t_s_env		*e;
	const char	*buff;
	size_t		buff_len;
	size_t		i;
}				t_exp;

typedef struct	s_expansion_handler
{
	char		c;
	int			(*handler)(t_exp *);
}				t_e_handler;

# define OP_EXP_BACKSLSH	{ '\\', expand_backslash }
# define OP_EXP_DOLLAR		{ '$',  expand_dollar }
# define OP_EXP_BACKTICK	{ '`',  expand_backtick }
# define OP_EXP_DQUOTE		{ '"',  expand_dquote }
# define OP_EXP_SQUOTE		{ '\'', expand_squote }
# define OP_EXP_TILDE		{ '~',  expand_tilde }
# define OP_EXP_STAR		{ '*',  expand_glob }
# define OP_EXP_BRACKET		{ '[',  expand_glob }
# define OP_EXP_QUESTION	{ '?',  expand_glob }

int				expand(const char *buff, t_m_list *list, t_s_env *e);
int				expand_mword(t_ret *ret, t_exp *param, int (*end)(t_exp *));
int				expand_error(int error, const char *progname);

int				expand_backslash(t_exp *param, t_ret *ret);
int				expand_dollar(t_exp *param, t_ret *ret);
int				expand_backtick(t_exp *param, t_ret *ret);
int				expand_dquote(t_exp *param, t_ret *ret);
int				expand_squote(t_exp *param, t_ret *ret);
int				expand_tilde(t_exp *param, t_ret *ret);
int				expand_glob(t_exp *param, t_ret *ret);

int				expand_dollar_parameter(t_exp *param, t_ret *ret);
int				expand_dollar_brace(t_ret *word, t_exp *param);
int				expand_dollar_subs(t_exp *param, t_ret *ret);

int				param_addchar(char c, t_ret *ret);
int				param_addstr(char *str, t_ret *ret);

#endif
