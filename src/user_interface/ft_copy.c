/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:36:28 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 11:46:03 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"

void		ft_copy(t_line *line)
{
	if (line->slct_beg < 0)
		return ;
	if (line->copy)
		free(line->copy);
	line->copy = ft_strndup(&(line->curr->buff[line->slct_beg]),
			line->slct_end - line->slct_beg);
}
