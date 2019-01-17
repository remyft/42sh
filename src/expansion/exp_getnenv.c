/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_getnenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 18:44:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/16 23:10:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_lib.h"

char			*exp_getnenv(const char *name, char **env)
{
	size_t		i;
	size_t		len;

	i = 0;
	if (!env || !name)
		return (NULL);
	len = ft_strlen(name);
	while (env[i])
	{
		if (exp_strncmp(env[i], name, len) == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}
