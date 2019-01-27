/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_stralnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 11:14:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 11:16:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				sh_stralnum(const char *str)
{
	size_t		i;

	i = 0;
	if (str)
		while (str[i])
			if (!ft_isalnum(str[i++]))
				return (0);
	return (1);
}