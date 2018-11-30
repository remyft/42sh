/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/01 00:49:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKEN_H
# define FT_TOKEN_H

# include <stdlib.h>
# include <stdio.h>

/*
** Token Types
*/
enum {
	UNDEFINED = -1,
	OPERATOR,
	TOKEN,
};

/*
** Token Specs for type TOKEN
*/
enum {
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	IO_NUMBER,
	RESERVED_WORD,
};

/*
** Token Specs for type OPERATOR
*/
# define OR_IF				{ "||",  0 }
# define PIPE				{ "|",   1 }
# define PIPE_AND			{ "|&",  2 }
# define NOT				{ "!",   3 }
# define AND_IF				{ "&&",  4 }
# define BACKGRND			{ "&",   5 }
# define SEMI				{ ";",   6 }
# define DSEMI				{ ";;",  7 }
# define PAREN_LEFT			{ "(",   8 }
# define PAREN_RIGHT		{ ")",   9 }
# define LESS				{ "<",   10 }
# define LESSAND			{ "<&",  11 }
# define LESS_GREAT			{ "<>",  12 }
# define GREAT				{ ">",   13 }
# define GREAT_PIPE			{ ">|",  14 }
# define AND_GREAT			{ "&>",  15 }
# define GREAT_AND			{ ">&",  16 }
# define DGREAT				{ ">>",  17 }
# define AND_DGREAT			{ "&>>", 18 }
# define DGREAT_AND			{ ">>&", 19 }
# define DLESS				{ "<<",  20 }
# define TLESS				{ "<<<", 21 }

/*
** Token Specs for type EXPANSION
*/
enum {
	PARAMETER,
	COMMAND,
	ARITHMETIC,
};

/*
** Token Specs for quotes
*/
enum {
	BACKSLASH = (1 << 0),
	SINGLE_QUOTE = (1 << 1),
	DOUBLE_QUOTE = (1 << 2),
};

/*
** Token structure
*/
typedef struct	s_token
{
	char			quote;
	int				type;
	int				spec;
	size_t			head;
	size_t			tail;
	char			*exp;
	struct s_token	*next;
}				t_token;

/*
** Handlers parameters structure
*/
typedef struct	s_param
{
	t_token		*token;
	const char	*buff;
	size_t		i;
}				t_param;

/*
** Typedefs for tokenisation
*/
# define ID_OPERATOR		{ identify_operator }
# define ID_TOKEN			{ identify_word }

typedef struct	s_call
{
	t_token		*(*identifier)(t_param *);
}				t_call;

# define CHAR_QUOTE			{ ft_isquote,     handle_quote }
# define CHAR_NEWLINE		{ ft_isnewline,   handle_newline }
# define CHAR_OPERATOR		{ ft_isoperator,  handle_operator }
# define CHAR_WORD			{ ft_isword,      handle_word }
# define CHAR_NULL			{ ft_isnull,      handle_end_of_input }

typedef struct	s_func
{
	int			(*is)(int);
	t_token		*(*handler)(t_param *, t_call *);
}				t_func;

/*
** Typedef for OPERATOR
*/
typedef struct	s_ope
{
	char		*name;
	size_t		value;
}				t_ope;

t_token			*get_tokens(const char *buff);
t_token			*new_token(int c, size_t pos);

int				is_token(int type);
int				is_operator(int type);
int				is_expansion(int type);

int				ft_isnewline(int c);
int				ft_isoperator(int c);
int				ft_isword(int c);
int				ft_isquote(int c);
int				ft_isnull(int c);
int				ft_isspec(int c);
int				ft_isname(int c);

t_token			*handle_quote(t_param *param, t_call *token);
t_token			*handle_newline(t_param *param, t_call *token);
t_token			*handle_operator(t_param *param, t_call *token);
t_token			*handle_word(t_param *param, t_call *token);
t_token			*handle_end_of_input(t_param *param, t_call *token);
t_token			*handle_expansion(t_param *param, t_call *token);

t_token			*identify_operator(t_param *param);
t_token			*identify_word(t_param *param);
t_token			*identify_quote(t_param *param);

void			get_commands(t_token *tokens);

#endif
