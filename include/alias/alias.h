/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:27:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/08 05:34:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

# include "token.h"

typedef struct	s_alias
{
	char			*key;
	char			*value;
	struct s_alias	*next;
	struct s_alias	*prev;
}				t_alias;

t_token				*alias_get(t_token *token, t_alias *alias);

#endif
