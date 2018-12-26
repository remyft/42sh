/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_addchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 23:59:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/26 10:39:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

int			param_addchar(char c, t_ret *ret)
{
	char	*save;

	save = NULL;
	if (ret->w_len == ret->w_max)
	{
		save = ret->word;
		ret->w_max += RET_CHUNK;
		if ((ret->word = ft_memalloc(ret->w_max)) == NULL)
			return (ERR_MALLOC);
	}
	if (ret->word)
	{
		if (save)
			ft_strcpy(ret->word, save);
		ret->word[ret->w_len++] = c;
	}
	if (save)
		free(save);
	return (ERR_NONE);
}
