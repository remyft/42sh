/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:09:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/27 19:30:42 by gbourgeo         ###   ########.fr       */
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
