/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 19:38:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/13 19:43:15 by gbourgeo         ###   ########.fr       */
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
