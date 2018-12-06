/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_subs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:57:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/06 19:58:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

int		ft_isbracket(const char *s)
{
	return ((*s == '}'));
}

int		ft_isdparen(const char *s)
{
	return (!ft_strncmp(s, "))", 2));
}

int		ft_isparen(const char *s)
{
	return ((*s == ')'));
}

int		ft_isnotname(const char *s)
{
	return (ft_isword(*s)
		&& !ft_isquote(*s)
		&& !ft_issubs(*s)
		&& !ft_isoperator(*s));
}

int		ft_isbackquote(const char *s)
{
	return ((*s == '`'));
}
