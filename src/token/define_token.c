/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:09:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/22 23:11:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

size_t			define_token(const char c)
{
	if (ft_strchr(OPERATORS, c))
		return (OPERATOR);
	else if (c == '\n')
		return (NEWLINE);
	else if (ft_isspace(c))
		return (NEW_INPUT);
	return (TOKEN);
}
