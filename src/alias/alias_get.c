/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:26:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/15 06:30:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "alias.h"

const char			*alias_get(const char *str, size_t len, t_alias *alias)
{
	if (!str || !alias || len == 0)
		return (NULL);
	while (alias->next)
	{
		if (!ft_strncmp(str, alias->key, len))
			return (alias->value);
		alias = alias->next;
	}
	return (NULL);
}
