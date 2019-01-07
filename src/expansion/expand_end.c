/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 22:29:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/06 23:27:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

int				expand_end(t_ret *ret, t_argument *arg)
{
	t_ret		*ptr;
	size_t		len;

	ptr = ret;
	len = 1;
	while (ptr->next && ++len)
		ptr = ptr->next;
	if (!(arg->list = ft_memalloc(sizeof(*arg->list) * (len + 1))))
		return (ERR_MALLOC);
	ptr = ret;
	len = 0;
	while (ptr)
	{
		arg->list[len++] = ptr->word;
		ptr->word = NULL;
		ptr = ptr->next;
	}
	free_t_ret(&ret);
	return (ERR_NONE);
}
