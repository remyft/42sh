/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:30:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/11 14:32:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isnull(const char *s)
{
	return ((*s == 0));
}

int			ft_isquote(int c)
{
	return ((c == '\\')
		|| (c == '\'')
		|| (c == '"')
		|| (c == '{')
		|| (c == '(')
		|| (c == '`'));
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
