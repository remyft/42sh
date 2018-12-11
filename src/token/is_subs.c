/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_subs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:57:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/11 14:31:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

int		ft_isbracket(const char *s)
{
	return ((*s == '{'));
}

int		ft_isparen(const char *s)
{
	return ((*s == '('));
}

int		ft_isnameend(const char *s)
{
	return (!ft_isalnum(*s));
}

int		ft_isbackquote(const char *s)
{
	return ((*s == '`'));
}
