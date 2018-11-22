/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/22 05:23:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKEN_H
# define FT_TOKEN_H

#include <stdlib.h>

# define NEW_INPUT			(1 << 0)
# define TOKEN				(1 << 1)
# define OPERATOR			(1 << 2)

# define WORD				(1 << 3)
# define ASSIGNMENT_WORD	(1 << 4)
# define NAME				(1 << 5)
# define NEWLINE			(1 << 6)
# define IO_NUMBER			(1 << 7)
# define RESERVERD_WORD		(1 << 8)

# define AND_IF				(1 << 9)
# define OR_IF				(1 << 10)
# define SEMI				(1 << 11)
# define DSEMI				(1 << 12)
# define DLESS				(1 << 13)
# define DGREAT				(1 << 14)
# define LESSAND			(1 << 15)
# define GREATAND			(1 << 16)
# define LESSGREAT			(1 << 17)
# define DLESSDASH			(1 << 18)
# define CLOBBER			(1 << 19)

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
void				get_commands(t_token *tokens);

#endif
