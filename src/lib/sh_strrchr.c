/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:29:49 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/27 14:19:29 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*sh_strrchr(const char *str, char c)
{
	int		i;
	char	*find;
	int		is_bslash;

	i = 0;
	find = NULL;
	is_bslash = 0;
	while (str[i])
	{
		if (is_bslash)
			is_bslash = 0;
		else if (str[i] == c)
			find = (char*)&str[i];
		if (str[i] == '\\')
			is_bslash = 1;
		i++;
	}
	return (find);
}
