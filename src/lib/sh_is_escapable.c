/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_is_escapable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 12:52:03 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/17 19:21:14 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		sh_is_escapable(char c)
{
	if (!ft_isalnum(c) && c != '/' && c != '.' && c != '_' && c != '-'
			&& c != '=')
		return (1);
	return (0);
}
