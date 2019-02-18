/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:26:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/17 22:16:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_alias.h"

t_alias			*alias_get(const char *str, size_t len, t_alias *alias)
{
	if (!str || !alias || len == 0)
		return (NULLALIAS);
	while (alias)
	{
		if (!ft_strncmp(str, alias->key, len) && !alias->in_use)
			return (alias);
		alias = alias->next;
	}
	return (NULLALIAS);
}
