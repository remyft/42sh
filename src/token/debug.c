/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:13:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/13 19:22:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

void			debug_tokens(const char *buff, t_token *tokens, char *stab)
{
	for (t_token *ptr = tokens; ptr; ptr = ptr->next) {
		printf("------------------------------\n"
				"%stype:%d spec:%d head:%ld tail:%ld\n", stab,
				ptr->type, ptr->spec, ptr->head, ptr->tail);
		printf("%sbuff: \"", stab); fflush(stdout);
		write(1, buff + ptr->head, ptr->tail - ptr->head);
		write(1, "\" command: \"", 12);
		if (ptr->command)
			write(1, ptr->command, ft_strlen(ptr->command));
		write(1, "\"\n", 2);
		if (ptr->subs)
			debug_tokens(buff, ptr->subs, ft_strjoin(stab, "\t"));
	}
	free(stab);
}