/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:20:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/24 02:41:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "shell_env.h"
# include "parser.h"

# define SEPARATORS		" \t\n"

enum
{
	ERR_NONE,
	ERR_MALLOC,
};

/*
** New token structure for nested expansions
*/
# define NULLEXPANSION	(t_expansion *)0

typedef struct	s_expansion
{
	int					type;
	size_t				head;
	size_t				tail;
	struct s_expansion	*next;
}				t_expansion;

typedef struct	s_expansion_param
{
	char		*ifs;
	const char	*buff;
	t_token		*token;
	size_t		i;
	t_expansion	*exp;
}				t_e_param;

int				expand(const char *buff, t_m_list *list, t_s_env *e);
int				expand_error(int error, t_s_env *e);

#endif
