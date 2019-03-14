/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:30:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/12 13:04:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isquote(int c)
{
	return ((c == '\\')
		|| (c == '\'')
		|| (c == '"')
		|| (c == '(')
		|| (c == '{')
		|| (c == ')')
		|| (c == '}')
		|| (c == '`'));
}

int			ft_iscomment(int c)
{
	return ((c == '#'));
}

int			ft_isequal(int c)
{
	return ((c == '='));
}

int			ft_isminus(int c)
{
	return ((c == '-'));
}

int			ft_isoperator(int c)
{
	return ((c == '&')
			|| (c == '|')
			|| (c == ';')
			|| (c == '<')
			|| (c == '>'));
}
