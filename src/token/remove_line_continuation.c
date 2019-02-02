/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_line_continuation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 01:42:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/30 20:23:46 by gbourgeo         ###   ########.fr       */
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
		else if (line[i] == '\\')
		{
			if (line[i + 1] == '\n')
			{
				if (!quote)
					ft_strcpy(line + i, line + i + 2);
			}
			else
				i++;
		}
		i++;
	}
	return (line);
}
