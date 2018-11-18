/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/18 19:21:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKEN_H
# define FT_TOKEN_H

# define EXECUTE		(1 << 0)
# define EXECUTE_IF_OK	(1 << 1)
# define EXECUTE_IF_NOT	(1 << 2)

# define WORDS			(1 << 0)
# define OPERATOR		(1 << 1)
# define QUOTED			(1 << 2)
# define DQUOTED		(1 << 3)

typedef struct      s_cmd
{
    char			type;
    char			*cmd;
	struct s_cmd	*left;
	struct s_cmd	*right;
}					t_cmd;

typedef struct		s_var
{
	unsigned int	i;
	unsigned int	j;
	char			quoted;
	char			rights;
}					t_var;

typedef struct		s_token
{
	char			rights;
	char			*line;
	t_cmd			*head;
	struct s_token	*next;
}					t_token;

t_token				*get_tokens(char *buff);
void				get_commands(t_token *tokens);

#endif
