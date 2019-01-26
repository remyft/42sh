/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_duplicate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:14:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/26 15:45:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**duplicate_environ(char **table)
{
	char		**ret;
	size_t		i;

	i = 0;
	while (table[i])
		i++;
	if (!(ret = ft_memalloc(sizeof(*ret) * (i + 1))))
		return (NULL);
	i = 0;
	while (table[i])
		if (!(ret[i] = ft_strdup(table[i])))
		{
			while (i--)
				free(ret[i]);
			free(ret);
			return (NULL);
		}
		else
			i++;
	return (ret);
}
