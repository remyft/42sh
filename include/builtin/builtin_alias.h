/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:27:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/17 22:11:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ALIAS_H
# define BUILTIN_ALIAS_H

# include "shell_env.h"

int					alias_set(char *key_value, t_alias **alias);
int					alias_set_value(char *value, t_alias *alias);
t_alias				*alias_new(char *key, char *value, t_alias *alias);

t_alias				*alias_get(const char *str, size_t len, t_alias *alias);

#endif
