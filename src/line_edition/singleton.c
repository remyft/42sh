/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:44:05 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/23 08:57:29 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"

t_line	*get_struct(void)
{
	static t_line	*line = NULL;

	if (!line)
		line = ft_memalloc(sizeof(t_line));
	return (line);
}
