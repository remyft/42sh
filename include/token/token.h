/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/28 06:43:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKEN_H
# define FT_TOKEN_H

# include <stdlib.h>
# include <stdio.h>

/*
** Token Types
*/
# define UNDEFINED			(1 << 0)
# define TOKEN				(1 << 1)
# define OPERATOR			(1 << 2)

/*
** Token Specs for type TOKEN
*/
# define WORD				(1 << 0)
# define ASSIGNMENT_WORD	(1 << 1)
# define NAME				(1 << 2)
# define NEWLINE			(1 << 3)
# define IO_NUMBER			(1 << 4)
# define RESERVED_WORD		(1 << 5)

/*
** Token Specs for type OPERATOR
*/
# define OR_IF				{ "||",  (1 << 0) }
# define PIPE				{ "|",   (1 << 1) }
# define PIPE_AND			{ "|&",  (1 << 2) }
# define NOT				{ "!",   (1 << 3) }
# define AND_IF				{ "&&",  (1 << 4) }
# define BACKGRND			{ "&",   (1 << 5) }
# define SEMI				{ ";",   (1 << 6) }
# define DSEMI				{ ";;",  (1 << 7) }
# define PAREN_LEFT			{ "(",   (1 << 8) }
# define PAREN_RIGHT		{ ")",   (1 << 9) }
# define LESS				{ "<",   (1 << 10) }
# define LESSAND			{ "<&",  (1 << 11) }
# define LESS_GREAT			{ "<>",  (1 << 12) }
# define GREAT				{ ">",   (1 << 13) }
# define GREAT_PIPE			{ ">|",  (1 << 14) }
# define AND_GREAT			{ "&>",  (1 << 15) }
# define GREAT_AND			{ ">&",  (1 << 16) }
# define DGREAT				{ ">>",  (1 << 17) }
# define AND_DGREAT			{ "&>>", (1 << 18) }
# define DGREAT_AND			{ ">>&", (1 << 19) }
# define DLESS				{ "<<",  (1 << 20) }
# define TLESS				{ "<<<", (1 << 21) }

/*
** Token structure
*/
typedef struct	s_token
{
	char			quoted;
	char			type;
	size_t			spec;
	size_t			head;
	size_t			tail;
	char			*exp;
	struct s_token	*next;
}				t_token;

/*
** Typedefs for tokenisation
*/
# define CHAR_QUOTE			{ ft_isquote,    quote_handler }
# define CHAR_NEWLINE		{ ft_isnewline,  end_of_input }
# define CHAR_OPERATOR		{ ft_isoperator, operator_handler }
# define CHAR_EXPANSION		{ ft_isexpansion,  expansion_handler }
# define CHAR_WORD			{ ft_isword,     word_handler }

typedef struct	s_func
{
	int			(*is)(int);
	t_token		*(*exec)(t_token *, const char *, size_t *);
}				t_func;

# define ID_TOKEN			{ TOKEN,    identify_token }
# define ID_OPERATOR		{ OPERATOR, identify_operator }

typedef struct	s_id
{
	char		type;
	t_token		*(*exec)(t_token *, const char *, size_t *);
}				t_id;

/*
** Typedef for operators
*/
typedef struct	s_ope
{
	char			*name;
	size_t			value;
}				t_ope;

t_token			*get_tokens(const char *buff);
t_token			*new_token(const char c, size_t pos);
size_t			define_token(const char c);

int				is_token(int type);
int				is_operator(int type);

int				ft_isnewline(int c);
int				ft_isoperator(int c);
int				ft_isword(int c);
int				ft_isquote(int c);
int				ft_isspec(int c);
int				ft_isexpansion(int c);

t_token			*operator_handler(t_token *tok, const char *buff, size_t *pos);
t_token			*word_handler(t_token *token, const char *buff, size_t *pos);
t_token			*quote_handler(t_token *token, const char *buff, size_t *pos);

t_token			*identify_operator(t_token *tok, const char *buff, size_t *pos);
t_token			*identify_token(t_token *token, const char *buff, size_t *pos);

void			get_commands(t_token *tokens);

#endif
