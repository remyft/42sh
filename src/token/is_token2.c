/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 10:22:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/12 11:18:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isword(int c)
{
	return ((c >= 0x21) && (c <= 0x7E));
}

int			ft_isname(int c)
{
	return (((c >= 0x07) && (c <= 0x0D))
			|| ((c >= 0x20) && (c <= 0x7E)));
}

int			ft_iscomment(int c)
{
	return ((c == '#'));
}

int			ft_iscommand(int c)
{
	return ((c == '{') || (c == '(')
		|| (c == '}') || (c == ')'));
}