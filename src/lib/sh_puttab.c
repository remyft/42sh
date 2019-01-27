/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_puttab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:30:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 10:31:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				sh_puttab(const char **env)
{
	size_t		i;

	i = 0;
	if (env)
		while (env[i])
			ft_putendl(env[i++]);
	return (0);
}
