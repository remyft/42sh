/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:13:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/14 15:32:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

void			debug_tokens(const char *buff, t_token *tokens)
{
	// int i = 0;
	// int val[] = { BACKSLASH, DOUBLE_QUOTE, SINGLE_QUOTE, PARENTHESE, BRACKET, BACKQUOTE, };
	// for (size_t j=0;j<sizeof(val)/sizeof(*val);j++)
	// {
	// 	i |= val[j];
	// 	printf("i=%d\n"
	// 			"%-2d %-2d %-2d %-2d\n"
	// 			"%-2d %-2d %-2d %-2d\n"
	// 			"%-2d %-2d %-2d %-2d\n"
	// 			"%-2d %-2d %-2d %-2d\n"
	// 			"%-2d %-2d %-2d %-2d\n"
	// 			"%-2d %-2d %-2d %-2d\n",
	// 			i,
	// 			i & val[0], ~(i | ~val[0]), !(i & val[0]), i & ~val[0],
	// 			i & val[1], ~(i | ~val[1]), !(i & val[1]), i & ~val[1],
	// 			i & val[2], ~(i | ~val[2]), !(i & val[2]), i & ~val[2],
	// 			i & val[3], ~(i | ~val[3]), !(i & val[3]), i & ~val[3],
	// 			i & val[4], ~(i | ~val[4]), !(i & val[4]), i & ~val[4],
	// 			i & val[5], ~(i | ~val[5]), !(i & val[5]), i & ~val[5]
	// 			);
	// 	// i &= ~val[j];
	// }

	for (t_token *ptr = tokens; ptr; ptr = ptr->next) {
		printf("------------------------------\n"
				"type:%d spec:%d head:%ld tail:%ld\n",
				ptr->type, ptr->spec, ptr->head, ptr->tail);
		printf("buff   : [%.*s]\n", (int)(ptr->tail - ptr->head), buff + ptr->head);
	}
}