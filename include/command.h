/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 00:55:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/18 02:45:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMMAND_H
# define FT_COMMAND_H

# include "token.h"

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

void				parse_commands(t_token *tokens);

#endif
