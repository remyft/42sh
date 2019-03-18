/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:36:28 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/14 16:16:44 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"
#include "shell_term.h"

void		ft_copy(t_line *line)
{
	int		tmp_end;

	tmp_end = line->slct_end;
	if (line->slct_beg < 0)
		return ;
	if (line->copy)
		free(line->copy);
	line->copy = ft_strndup(&(line->curr->buff[line->slct_beg]),
			line->slct_end - line->slct_beg);
	while (line->slct_end != (int)line->index && tmp_end > line->slct_beg)
	{
		line->slct_beg == (int)line->index ? left_arrow(line)
			: right_arrow(line);
		tmp_end -= 1;
	}
}
