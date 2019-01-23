/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_validname.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 05:46:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/23 05:46:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

int			ft_isvalidname(t_param *param)
{
	const char	*str;
	size_t		n;

	str = param->token->head;
	n = param->i - (size_t)(param->token->head - param->buff);
	if (!n || ft_isdigit(*str))
		return (0);
	while (n--)
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		else
			str++;
	return (1);
}
