/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:20:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/07 16:19:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "token.h"

static t_token	*tokenize(t_param *param, t_call *token)
{
	static t_func	character[] = {
		CHAR_QUOTE, CHAR_COMMENT, CHAR_SUBS, CHAR_NEWLINE, CHAR_OPERATOR,
		CHAR_WORD
	};
	size_t			i;
	size_t			size;

	i = 0;
	size = (param->token->quote) ? 1 : sizeof(character) / sizeof(*character);
	if (param->token->type == UNDEFINED)
		param->token->head = param->i;
	while (i < size)
	{
		if (character[i].is(param->buff[param->i]))
			return (character[i].handler(param, token));
		i++;
	}
	if (!param->token->quote && !(param->token->type == UNDEFINED))
		return (token[param->token->type].identifier(param));
	return (param->token);
}

t_token			*get_tokens(const char *buff, size_t i,
							int (*ft_end)(const char *))
{
	static t_call	token[] = {
		ID_OPERATOR, ID_TOKEN,
	};
	t_token			*head;
	t_param			param;

	head = new_token(buff[i], i);
	param.token = head;
	param.buff = buff;
	param.i = i;
	while (param.token)
	{
		if (ft_end(param.buff + param.i))
			param.token = handle_end_of_input(&param, token);
		else if (ft_end != ft_isnotname && param.token->spec == COMMENT)
		{
			if (ft_isendl(param.buff + param.i))
				param.token = token[param.token->type].identifier(&param);
		}
		else
			param.token = tokenize(&param, token);
		param.i++;
	}
#ifdef DEBUG
			for (t_token *ptr = head; ptr; ptr = ptr->next) {
			printf("------------------------------\n"
					"type:%d spec:%d head:%ld tail:%ld quoted:%c\n",
					ptr->type, ptr->spec, ptr->head, ptr->tail, ptr->quote);
			write(1, "command: \"", 10);
			write(1, buff + ptr->head, ptr->tail - ptr->head);
			write(1, "\"\n", 2);
			// for (t_token *ptr2 = ptr->subs; ptr2; ptr2 = ptr2->next) {
			// 	printf("------------------------------\n"
			// 			"\ttype:%d spec:%d head:%ld tail:%ld quoted:%c\n",
			// 			ptr2->type, ptr2->spec, ptr2->head, ptr2->tail, ptr2->quote);
			// 	write(1, "\tcommand: \"", 11);
			// 	write(1, line->buff + ptr2->head, ptr2->tail - ptr2->head);
			// 	write(1, "\"\n", 2);
			// 	}
			}
#endif
	return (head);
}
