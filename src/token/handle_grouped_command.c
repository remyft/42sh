/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_grouped_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:42:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/05 21:21:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int		check_quote(t_quote *head, int type)
{
	if (!head)
		return (1);
	if (head->next)
		return (check_quote(head->next, type));
	return (head->type == type);
}

static t_quote		*quote_add(t_quote **head, int type)
{
	t_quote			*ptr;

	ptr = *head;
	if (*head)
		(*head)->next = quote_add(&(*head)->next, type);
	else if ((*head = ft_memalloc(sizeof(**head))))
	{
		(*head)->type = type;
		return (*head);
	}
	if (*head && !(*head)->next)
		free(*head);
	return (NULLQUOTE);
}

static t_token	*parent(t_param *param)
{
	// if (param->token->quote && param->token->quote != PARENTHESE)
	// 	return (param->token);
	// param->token->quote |= PARENTHESE;
	// param->token->depth++;
	// return (param->token);

	// if the parenthese is quoted do nothing
	if (param->token->quoted)
		return (param->token);
	// Add parenthese to the quote list
	if (!quote_add(&param->token->quote, PARENTHESE))
		return (NULLTOKEN);
	return (param->token);
}

static t_token	*parentend(t_param *param)
{
	if (!param->token->quote || param->token->quote & ~PARENTHESE)
		return (param->token);
	if (--param->token->depth == 0)
		param->token->quote &= ~PARENTHESE;
	return (param->token);
}

t_token			*handle_grouped_command(t_param *param, t_call *token)
{
	static t_quote_h	quote[] = {
		{ '(', parent },
		{ ')', parentend },
	};
	size_t				i;

	i = 0;
	if (param->token->type == UNDEFINED)
		param->token->type = TOKEN;
	else if (param->token->type != TOKEN)
		param->token = token[OPERATOR].identifier(param);
	while (i < sizeof(quote) / sizeof(*quote))
	{
		if (param->buff[param->i] == quote[i].value)
			return (quote[i].handler(param));
		i++;
	}
	return (param->token);
}
