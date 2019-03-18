/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:13:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/13 12:10:48 by gbourgeo         ###   ########.fr       */
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
	t_quote		*quote;

	ptr = tokens;
	ft_dprintf(2, "------------------------------\n");
	while (ptr)
	{
		ft_dprintf(2, "type: %d id: %d\nbuff: [", ptr->type, ptr->id);
		write(2, ptr->head, ptr->len);
		ft_dprintf(2, "] %ld", ptr->len);
		if ((quote = ptr->quote))
			ft_dprintf(2, "\nQuoted:");
		while (quote)
		{
			ft_dprintf(2, " %d", quote->type);
			quote = quote->next;
		}
		ft_dprintf(2, "\n");
		ptr = ptr->next;
	}
	ft_dprintf(2, "------------------------------\n");
}

#endif
