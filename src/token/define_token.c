/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:09:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/27 02:51:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

size_t	define_token(const char c)
{
	if (ft_isspace(c))
		return (UNDEFINED);
	if (ft_isoperator(c))
		return (OPERATOR);
	return (TOKEN);
}

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
	return (!ft_isspace(c));
}

int		ft_isquote(int c)
{
	return ((c == '\\') || (c == '\'') || (c == '"'));
}
