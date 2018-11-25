/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:54:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/26 00:55:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

t_token			*word_handler(t_token *token, const char *buff, size_t pos)
{
	token->tail = pos;
	if (ft_isspace(buff[token->head]))
		token->head = pos;
	if (token->type & NEW_INPUT)
		token->type = TOKEN;
	if (token->type & OPERATOR)
		return (identify_operator(token, buff, pos));
	return (token);
}
