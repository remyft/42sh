/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:30:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/30 23:49:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isnewline(int c)
{
	return ((c == '\n') || (c == '\r'));
}

int		ft_isoperator(int c)
{
	return ((c == '&')
			|| (c == '|')
			|| (c == ';')
			|| (c == '<')
			|| (c == '>')
			|| (c == '!'));
}

int		ft_isword(int c)
{
	return ((c == 0x07) || ((c >= 0x21) && (c <= 0x7E)));
}

int		ft_isquote(int c)
{
	return ((c == '\\') || (c == '\'') || (c == '"'));
}

int		ft_isexpansion(int c)
{
	return ((c == '$') || (c == '`'));
}
