/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:13:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/23 22:00:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "token.h"

#ifndef DEBUG

void			debug_tokens(t_token *tokens)
{
	(void)tokens;
}

#else

void			debug_tokens(t_token *tokens)
{
	t_token		*ptr;

	ptr = tokens;
	ft_dprintf(2, "------------------------------\n");
	while (ptr)
	{
		ft_dprintf(2, "type: %d id: %d\nbuff: [", ptr->type, ptr->id);
		write(2, ptr->head, ptr->len);
		ft_dprintf(2, "] %ld\n", ptr->len);
		ptr = ptr->next;
	}
	ft_dprintf(2, "------------------------------\n");
}

#endif
