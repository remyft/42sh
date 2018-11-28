/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:54:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/28 03:07:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token			*word_handler(t_token *token, const char *buff, size_t *pos)
{
	if (token->type & OPERATOR)
		return (identify_operator(token, buff, pos));
	token->tail = *pos;
	token->type = TOKEN;
	return (token);
}
