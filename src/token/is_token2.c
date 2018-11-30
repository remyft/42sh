/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 10:22:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/01 00:45:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isnull(int c)
{
	return ((c == 0));
}

int			ft_isname(int c)
{
	return ((c == '_') || ft_isalnum(c));
}
