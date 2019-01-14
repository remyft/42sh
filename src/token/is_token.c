/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:30:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/12 12:28:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isquote(int c)
{
	return ((c == '\\') || (c == '\'') || (c == '"'));
}

int			ft_issubs(int c)
{
	return ((c == '$') || (c == '`'));
}

int			ft_isnewline(int c)
{
	return ((c == '\n') || (c == '\r'));
}

int			ft_isoperator(int c)
{
	return ((c == '&')
			|| (c == '|')
			|| (c == ';')
			|| (c == '<')
			|| (c == '>')
			|| (c == '!'));
}

int			ft_isequal(int c)
{
	return ((c == '='));
}
