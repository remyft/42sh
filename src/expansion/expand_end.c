/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 22:29:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/22 03:46:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

int				expand_end(t_ret *ret, t_argument *arg)
{
	t_ret		*ptr;
	size_t		len;
	char		*alias;

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
		alias = NULL;
		if (arg->token->alias && arg->token->alen
		&& (alias = ft_strndup((char *)arg->token->alias, arg->token->alen)))
			ptr->word = ft_strjoinfree(ptr->word, alias, 3);
		arg->cmd[len++] = ptr->word;
		ptr->word = NULL;
		ptr = ptr->next;
	}
	return (ERR_NONE);
}
