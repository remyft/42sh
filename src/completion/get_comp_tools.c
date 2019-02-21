/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comp_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 17:00:18 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/08 17:01:16 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "libft.h"

int			check_is_file(char *buff, t_line *line)
{
	int		i;

	i = line->len - 1;
	while (i >= 0 && !ft_strchr("&;| ", buff[i]))
		i--;
	while (i >= 0 && (buff[i] == ' ' || buff[i] == '\t'))
		i--;
	if (i == -1 || ft_strchr(";&|", buff[i]))
		return (0);
	return (1);
}

int			search_to_tmp(char *buff)
{
	int		i;

	i = -1;
	while (buff[++i])
		if (buff[i] == '~' || buff[i] == '/')
			return (1);
	return (0);
}
