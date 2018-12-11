/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_subs2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 01:43:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/11 14:31:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isbracketend(const char *s)
{
	return ((*s == '}'));
}

int		ft_isparenend(const char *s)
{
	return ((*s == ')'));
}

int		ft_isendl(const char *s)
{
	return ((*s == '\n') || (*s == '\0'));
}
