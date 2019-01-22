/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 10:22:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/22 06:14:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

int			ft_isvalidname(t_param *param)
{
	const char	*str;
	size_t		n;

	str = param->buff + param->token->head;
	n = param->i - param->token->head;
	if (!n || ft_isdigit(*str))
		return (0);
	while (n--)
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		else
			str++;
	return (1);
}

int			ft_isword(int c)
{
	return ((c >= 0x21) && (c <= 0x7E));
}

int			ft_isname(int c)
{
	return (((c >= 0x07) && (c <= 0x0D))
			|| ((c >= 0x20) && (c <= 0x7E)));
}

int			ft_iscomment(int c)
{
	return ((c == '#'));
}

int			ft_iscommand(int c)
{
	return ((c == '{') || (c == '(')
		|| (c == '}') || (c == ')'));
}
