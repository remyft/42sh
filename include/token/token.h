/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/26 00:42:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKEN_H
# define FT_TOKEN_H

# include <stdlib.h>
# include <stdio.h>

# define NEW_INPUT			(1 << 0)
# define TOKEN				(1 << 1)
# define OPERATOR			(1 << 2)

# define WORD				(1 << 3)
# define ASSIGNMENT_WORD	(1 << 4)
# define NAME				(1 << 5)
# define NEWLINE			(1 << 6)
# define IO_NUMBER			(1 << 7)
# define RESERVED_WORD		(1 << 8)

# define OR_IF				{ "||",  (1 << 3) }
# define PIPE				{ "|",   (1 << 4) }
# define PIPE_AND			{ "|&",  (1 << 5) }
# define NOT				{ "!",   (1 << 6) }
# define AND_IF				{ "&&",  (1 << 7) }
# define BACKGRND			{ "&",   (1 << 8) }
# define SEMI				{ ";",   (1 << 9) }
# define DSEMI				{ ";;",  (1 << 10) }
# define PAREN_LEFT			{ "(",   (1 << 11) }
# define PAREN_RIGHT		{ ")",   (1 << 12) }
# define LESS				{ "<",   (1 << 13) }
# define LESSAND			{ "<&",  (1 << 14) }
# define LESS_GREAT			{ "<>",  (1 << 15) }
# define GREAT				{ ">",   (1 << 16) }
# define GREAT_PIPE			{ ">|",  (1 << 17) }
# define AND_GREAT			{ "&>",  (1 << 18) }
# define GREAT_AND			{ ">&",  (1 << 19) }
# define DGREAT				{ ">>",  (1 << 20) }
# define AND_DGREAT			{ "&>>", (1 << 21) }
# define DGREAT_AND			{ ">>&", (1 << 22) }
# define DLESS				{ "<<",  (1 << 23) }
# define TLESS				{ "<<<", (1 << 24) }

# define OPERATORS			"&|;<>!"

typedef struct	s_ope
{
	char			*name;
	size_t			value;
}				t_ope;

typedef struct	s_token
{
	char			quoted;
	size_t			type;
	size_t			head;
	size_t			tail;
	struct s_token	*next;
}				t_token;

t_token			*get_tokens(const char *buff);
t_token			*new_token(const char c, size_t pos);
size_t			define_token(const char c);
t_token			*operator_handler(t_token *tail, const char *buff, size_t pos);
t_token			*identify_operator(t_token *token, const char *buff, size_t pos);
t_token			*word_handler(t_token *token, const char *buff, size_t pos);
t_token			*identify_token(t_token *token, const char *buff, size_t pos);
int				backslash_handler(const char *buff, size_t i);
void			get_commands(t_token *tokens);

#endif
