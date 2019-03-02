/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 22:29:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/02 15:37:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"
	#include <stdio.h>
int				expand_end(t_ret *ret, t_argument *arg)
{
	t_ret		*ptr;
	size_t		len;

	ptr = ret;
	len = 1;
	while (ptr->next && ++len)
		ptr = ptr->next;
	if (!(arg->cmd = ft_memalloc(sizeof(*arg->cmd) * (len + 1))))
		return (ERR_MALLOC);
	ptr = ret;
	len = 0;
	while (ptr)
	{
		printf("ptr: %s\n", ptr->word);
		arg->cmd[len++] = ptr->word;
		ptr->word = NULL;
		ptr = ptr->next;
	}
	return (ERR_NONE);
}
