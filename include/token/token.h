/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:24:35 by gbourgeo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/12/12 18:43:02 by gbourgeo         ###   ########.fr       */
=======
/*   Updated: 2018/12/12 17:09:41 by rfontain         ###   ########.fr       */
>>>>>>> 4137f821b52167f44df66f9e33c3d98e0baeea9d
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
	DOUBLE_QUOTE = (1 << 1),
	SINGLE_QUOTE = (1 << 2),
	PARENTHESE = (1 << 3),
	BRACKET = (1 << 4),
	BACKQUOTE = (1 << 5),
};

/*
** Token structure
*/
typedef struct	s_token
{
	int				quote;
	size_t			head;
	size_t			tail;
	struct s_token	*next;

	size_t			depth;
	int				type;
	int				spec;
	struct s_token	*subs;
	char			*command;
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
# define CHAR_CMD			{ ft_iscommand,  handle_command }
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
t_token			*tokenise(const char *buff);
t_token			*token_loop(t_param *param, int (*ft_end)(t_param *));
t_token			*new_token(int c, size_t pos);

t_token			*handle_end_of_input(t_param *param, t_call *token);
t_token			*handle_quote(t_param *param, t_call *token);
t_token			*handle_command(t_param *param, t_call *token);
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

int				ft_isnull(t_param *param);
int				ft_isendl(t_param *param);
int				ft_isbracket(t_param *param);
int				ft_isdparen(t_param *param);
int				ft_isparen(t_param *param);
int				ft_isnameend(t_param *param);
int				ft_isbackquote(t_param *param);
int				ft_isbracketend(t_param *param);
int				ft_isdparenend(t_param *param);
int				ft_isparenend(t_param *param);
int				ft_iscommand(int c);

#endif
