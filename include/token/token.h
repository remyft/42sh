/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/05 21:15:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>
# include <stdio.h>
# include "shell_env.h"

/*
** Token Types
*/
enum {
	UNDEFINED = -1,
	TOKEN,
	OPERATOR,
};

/*
** Identifiers for token TOKEN
*/
enum {
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	IO_NUMBER,
	RESERVED_WORD,
	COMMENT,
	SUBS,
};

/*
** Enumeration for \, ', ", (, `.
*/
enum {
	BACKSLASH = (1 << 0),
	DOUBLE_QUOTE = (1 << 1),
	SINGLE_QUOTE = (1 << 2),
	PARENTHESE = (1 << 3),
	BACKQUOTE = (1 << 4),
};

/*
** Quote main structure
*/
# define NULLQUOTE	(t_quote *)0

typedef struct	s_quote
{
	int				type;
	struct s_quote	*next;
}				t_quote;

/*
** Structure for TOKENS
*/
# define NULLTOKEN	(t_token *)0

typedef struct	s_token
{
	int				quoted;
	const char		*head;
	size_t			len;
	struct s_token	*next;

	t_quote			*quote;
	size_t			depth;
	int				type;
	int				id;
	struct s_token	*prev;
}				t_token;

/*
** Structure of parameters
** to pass to functions handling characters.
*/

typedef struct	s_param
{
	t_s_env		*e;
	t_token		*token;
	const char	*buff;
	size_t		i;
	t_token		*head;
}				t_param;

/*
** Structure for quote function handler
*/

typedef struct	s_quote_handler
{
	char		value;
	t_token		*(*handler)(t_param *);
}				t_quote_h;

/*
** Structure for OPERATORs, see above
*/
typedef struct	s_ope
{
	char		*name;
	size_t		value;
}				t_ope;

/*
** Token identifiers
*/
# define ID_OPERATOR		{ identify_operator }
# define ID_TOKEN			{ identify_word }

typedef struct	s_call
{
	t_token		*(*identifier)(t_param *);
}				t_call;

/*
** Characters Handler
*/
# define CHAR_QUOTE			{ ft_isquote,    handle_quote }
# define CHAR_CMD			{ ft_iscommand,  handle_grouped_command }
# define CHAR_SUBS			{ ft_issubs,     handle_subs }
# define CHAR_COMMENT		{ ft_iscomment,  handle_comment }
# define CHAR_NEWLINE		{ ft_isnewline,  handle_newline }
# define CHAR_EQUAL			{ ft_isequal,    handle_equal }
# define CHAR_MINUS			{ ft_isminus,    handle_minus }
# define CHAR_OPERATOR		{ ft_isoperator, handle_operator }
# define CHAR_WORD			{ ft_isword,     handle_word }

typedef struct	s_func
{
	int			(*is)(int);
	t_token		*(*handler)(t_param *, t_call *);
}				t_func;

/*
** Functions
*/
t_token			*tokenise(const char *buff, t_s_env *e);
t_token			*token_loop(t_param *param, int (*ft_end)(t_param *));
t_token			*new_token(const char *buff, size_t pos);
void			free_token(t_token **token);

t_token			*handle_alias(t_param *param, t_s_env *e);
t_token			*handle_grouped_command(t_param *param, t_call *token);
t_token			*handle_comment(t_param *param, t_call *tokens);
t_token			*handle_equal(t_param *param, t_call *token);
t_token			*handle_end_of_input(t_param *param, t_call *token);
t_token			*handle_minus(t_param *param, t_call *token);
t_token			*handle_newline(t_param *param, t_call *token);
t_token			*handle_operator(t_param *param, t_call *token);
t_token			*handle_quote(t_param *param, t_call *token);
t_token			*handle_subs(t_param *param, t_call *token);
t_token			*handle_word(t_param *param, t_call *token);

size_t			check_operator(t_token *token, size_t len);
t_token			*identify_operator(t_param *param);
t_token			*identify_word(t_param *param);

char			*expand_word(t_token *token);

int				ft_iscommand(int c);
int				ft_iscomment(int c);
int				ft_isequal(int c);
int				ft_isname(int c);
int				ft_isnewline(int c);
int				ft_isminus(int c);
int				ft_isoperator(int c);
int				ft_isquote(int c);
int				ft_issubs(int c);
int				ft_isword(int c);

int				ft_isbackquote(t_param *param);
int				ft_isbracket(t_param *param);
int				ft_isbracketend(t_param *param);
int				ft_isdparen(t_param *param);
int				ft_isdparenend(t_param *param);
int				ft_isendl(t_param *param);
int				ft_isnameend(t_param *param);
int				ft_isnull(t_param *param);
int				ft_isparen(t_param *param);
int				ft_isparenend(t_param *param);
int				ft_isspecial(t_param *param);
int				ft_isspecialend(t_param *param);

int				is_token_valid_name(t_param *param);
int				is_alias_valid_name(const char *alias, size_t len);

void			debug_tokens(t_token *tokens);

#endif
