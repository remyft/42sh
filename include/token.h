/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/21 23:42:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKEN_H
# define FT_TOKEN_H

# define END_OF_INPUT		(1 << 0)
# define WORD				(1 << 1)
# define ASSIGNMENT_WORD	(1 << 2)
# define NAME				(1 << 3)
# define NEWLINE			(1 << 4)
# define IO_NUMBER			(1 << 5)
# define RESERVERD_WORD		(1 << 6)
# define OPERATOR			(1 << 7)

# define AND_IF				(1 << 8)
# define OR_IF				(1 << 9)
# define SEMI				(1 << 10)
# define DSEMI				(1 << 11)
# define DLESS				(1 << 12)
# define DGREAT				(1 << 13)
# define LESSAND			(1 << 14)
# define GREATAND			(1 << 15)
# define LESSGREAT			(1 << 16)
# define DLESSDASH			(1 << 17)
# define CLOBBER			(1 << 18)

# define OPERATORS			"&|;<>&"

typedef struct		s_operator
{
	char			*name;
	size_t			value;
}					t_ope;

typedef struct		s_token
{
	size_t			type;
	size_t			head;
	size_t			tail;
	struct s_token	*next;
}					t_token;

t_token				*get_tokens(const char *buff, size_t i, char quoted);
void				get_commands(t_token *tokens);

#endif
