/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:30:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/27 23:33:00 by gbourgeo         ###   ########.fr       */
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
	return (!ft_isspace(c));
}

int		ft_isquote(int c)
{
	return ((c == '\\') || (c == '\'') || (c == '"'));
}

int		ft_isspec(int c)
{
	return ((c == '$') || (c == '`'));
}