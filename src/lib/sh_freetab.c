/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 11:28:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/28 11:33:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void			sh_freetab(char ***table)
{
	size_t		i;

	i = 0;
	if (table)
		if (*table)
			while ((*table)[i])
			{
				free((*table)[i]);
				(*table)[i] = NULL;
				i++;
			}
	if (table)
		*table = (char **)0;
}