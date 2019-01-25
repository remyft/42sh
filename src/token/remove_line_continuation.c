/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_line_continuation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 01:42:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/01 01:56:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*remove_line_continuation(char *line)
{
	size_t		i;
	char		quote;

	i = 0;
	quote = 0;
	if (!line)
		return (line);
	while (line[i])
	{
		if (line[i] == '\'')
			quote = !quote;
		if (!quote && line[i] == '\\' && line[i + 1] == '\n')
			ft_strcpy(line + i, line + i + 2);
		i++;
	}
	return (line);
}
