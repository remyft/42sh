/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_newenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 02:45:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/16 23:20:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "free_env.h"

char			**exp_newenv(char ***env)
{
	char		**save;
	size_t		len;

	save = *env;
	len = 0;
	while (save && save[len])
		len++;
	if (!(*env = ft_memalloc(sizeof(**env) * (len + 2))))
	{
		*env = save;
		return (NULL);
	}
	len = 0;
	while (save && save[len])
	{
		(*env)[len] = save[len];
		len++;
	}
	free(save);
	return (&(*env)[len]);
}
