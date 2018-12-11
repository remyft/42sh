/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/11 14:21:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>
# include <stdio.h>

# define NULLTOKEN	(t_token *)0

/*
** Token Types
*/
enum {
	UNDEFINED = -1,
	TOKEN,
	OPERATOR,
};

/*
** Specificities for token TOKEN
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
** Enumeration for '\', ''', '"'.
*/
enum {
	BACKSLASH = (1 << 0),
	SINGLE_QUOTE = (1 << 1),
	DOUBLE_QUOTE = (1 << 2),
	BRACKET = (1 << 3),
	PARENTHESE = (1 << 4),
};

/*
** Token structure
*/
typedef struct	s_token
{
	int				quote;
	int				type;
	int				spec;
	size_t			head;
	size_t			tail;
	struct s_token	*subs;
	char			*command;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

/*
** Structure of parameters
** to pass to functions handling characters.
*/
typedef struct	s_param
{
	t_token		*token;
	const char	*buff;
	size_t		i;
	size_t		depth;
}				t_param;

/*
** Typedef for QUOTES
*/

typedef struct	s_quote
{
	char		value;
	t_token		*(*handler)(t_param *);
}				t_quote;

/*
** Typedef for OPERATORs, see above
*/
typedef struct	s_ope
{
	char		*name;
	size_t		value;
}				t_ope;

/*
** Token identification
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
# define CHAR_SUBS			{ ft_issubs,     handle_subs }
# define CHAR_NEWLINE		{ ft_isnewline,  handle_newline }
# define CHAR_COMMENT		{ ft_iscomment,  handle_comment }
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
t_token			*tokenise(const char *buff, size_t i, \
						int (*ft_end)(const char *), size_t depth);
t_token			*new_token(int c, size_t pos);

t_token			*get_subs(t_param *param, int (*ft_end)(const char*), size_t i);

t_token			*handle_end_of_input(t_param *param, t_call *token);
t_token			*handle_quote(t_param *param, t_call *token);
t_token			*handle_subs(t_param *param, t_call *token);
t_token			*handle_newline(t_param *param, t_call *token);
t_token			*handle_comment(t_param *param, t_call *tokens);
t_token			*handle_operator(t_param *param, t_call *token);
t_token			*handle_word(t_param *param, t_call *token);

t_token			*identify_operator(t_param *param);
t_token			*identify_word(t_param *param);

char			*expand_word(const char *buff, t_token *token);

int				ft_isquote(int c);
int				ft_issubs(int c);
int				ft_isnewline(int c);
int				ft_isoperator(int c);
int				ft_isword(int c);
int				ft_isname(int c);
int				ft_iscomment(int c);

int				ft_isnull(const char *s);
int				ft_isendl(const char *s);
int				ft_isbracket(const char *s);
int				ft_isdparen(const char *s);
int				ft_isparen(const char *s);
int				ft_isnameend(const char *s);
int				ft_isbackquote(const char *s);
int				ft_isbracketend(const char *s);
int				ft_isdparenend(const char *s);
int				ft_isparenend(const char *s);

#endif
