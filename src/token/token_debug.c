/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tdebug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:13:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/23 02:33:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
	while (ptr)
	{
		printf("------------------------------\n"
				"type:%d id:%d\n", ptr->type, ptr->id);
		printf("buff   : [%.*s]\n", (int)ptr->len, ptr->head);
		ptr = ptr->next;
	}
}

#endif
