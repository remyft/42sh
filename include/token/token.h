/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/22 23:10:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKEN_H
# define FT_TOKEN_H

#include <stdlib.h>
#include <stdio.h>

# define NEW_INPUT			(1 << 0)
# define TOKEN				(1 << 1)
# define OPERATOR			(1 << 2)

# define WORD				(1 << 3)
# define ASSIGNMENT_WORD	(1 << 4)
# define NAME				(1 << 5)
# define NEWLINE			(1 << 6)
# define IO_NUMBER			(1 << 7)
# define RESERVED_WORD		(1 << 8)

# define AND_IF				(1 << 3)
# define OR_IF				(1 << 4)
# define SEMI				(1 << 5)
# define DSEMI				(1 << 6)
# define DLESS				(1 << 7)
# define DGREAT				(1 << 8)
# define LESSAND			(1 << 9)
# define GREATAND			(1 << 10)
# define LESSGREAT			(1 << 11)
# define DLESSDASH			(1 << 12)
# define CLOBBER			(1 << 13)

# define OPERATORS			"&|;<>"

typedef struct		s_operator
{
	char			*name;
	size_t			value;
}					t_ope;

typedef struct		s_token
{
	char			quoted;
	size_t			type;
	size_t			head;
	size_t			tail;
	struct s_token	*next;
}					t_token;

t_token				*get_tokens(const char *buff, size_t i);
t_token				*new_token(const char c, size_t pos);
size_t				define_token(const char c);
t_token				*identify_token(t_token *token, const char *buff, size_t pos);
void				get_commands(t_token *tokens);

#endif
