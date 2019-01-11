/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tdebug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:13:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/10 23:49:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

#ifndef DEBUG

void			debug_tokens(const char *buff, t_token *tokens)
{
	(void)buff;
	(void)tokens;
}

#else

void			debug_tokens(const char *buff, t_token *tokens)
{
	t_token		*ptr;

	ptr = tokens;
	while (ptr)
	{
		printf("------------------------------\n"
				"type:%d id:%d head:%ld tail:%ld\n",
				ptr->type, ptr->id, ptr->head, ptr->tail);
		printf("buff   : [%.*s]\n", (int)(ptr->tail - ptr->head),
									buff + ptr->head);
		ptr = ptr->next;
	}
}

#endif
