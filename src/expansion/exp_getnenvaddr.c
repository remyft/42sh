/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_getnenvaddr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 02:43:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/04 02:47:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_lib.h"

char			**exp_getnenvaddr(const char *name, char **env)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = (name) ? ft_strlen(name) : 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (exp_strncmp(env[i], name, len) == '=')
			return (env + i);
		i++;
	}
	return (NULL);
}
