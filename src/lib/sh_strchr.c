/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:24:41 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/27 13:36:00 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*sh_strchr(const char *str, char c)
{
	int		i;
	char	*find;
	int		is_bslash;

	i = 0;
	find = (char*)str;
	is_bslash = 0;
	while (str[i] && (str[i] != c || is_bslash))
	{
		if (is_bslash)
			is_bslash = 0;
		if (str[i] == '\\')
			is_bslash = 1;
		i++;
	}
	if (str[i] == c && !is_bslash)
		return (&find[i]);
	return (NULL);
}
