/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:27:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/15 06:21:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

# include <sys/types.h>

typedef struct	s_alias
{
	char			*key;
	char			*value;
	struct s_alias	*next;
	struct s_alias	*prev;
}				t_alias;

const char			*alias_get(const char *str, size_t len, t_alias *alias);

#endif
