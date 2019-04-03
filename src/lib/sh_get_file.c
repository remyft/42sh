/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:57:01 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/03 20:57:18 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_lib.h"
#include "libft.h"

char	*sh_get_file(int fd)
{
	char	*line;
	char	buff[1024];
	int		nb_read;

	line = NULL;
	ft_bzero(buff, 1024);
	while ((nb_read = read(fd, buff, 1023)) > 0)
	{
		buff[nb_read] = '\0';
		if (line)
			line = ft_strjoinfree(line, buff, 1);
		else
			line = ft_strdup(buff);
	}
	return (line);
}
