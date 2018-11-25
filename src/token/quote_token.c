/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 19:23:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/26 00:54:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

int			backslash_handler(const char *buff, size_t i)
{
	if (buff[i + 1] == '\n')
	{
		ft_strcpy((char *)buff + i, (char *)buff + i + 2);
		return (i);
	}
	return (i + 2);
}
