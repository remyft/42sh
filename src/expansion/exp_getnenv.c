/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_getnenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 18:44:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/04 02:48:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_lib.h"

char			*exp_getnenv(const char *name, char **env)
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
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}
