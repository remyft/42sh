/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_glob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 23:31:08 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/15 00:18:41 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"

static int		deal_check(char **src, char **targ)
{
	if (**src == '*')
	{
		return (deal_star(src, targ));
	}
	else if (**src == '[')
	{
		if (!deal_bracket(src, targ))
			return (0);
	}
	else if (**src == **targ || (**src == '?' && **targ))
	{
		*src += 1;
		*targ += 1;
	}
	else
		return (0);
	return (2);
}

int				check_mln(char *src, char *targ)
{
	int state;
	int tmp;

	state = 0;
	while (*src)
	{
		if (!*targ)
			break ;
		if ((tmp = deal_check(&src, &targ)) != 2)
			return (tmp);
	}
	while (*src == '*')
		src++;
	if (*src == '/')
		src++;
	if (!*src && !*targ)
		return (1);
	return (0);
}
