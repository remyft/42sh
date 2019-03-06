/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end_of_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 23:42:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/06 17:09:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static void		clean_end_token(t_token **token, t_token **head)
{
	if (!*token)
		return ;
	if ((*token)->type != UNDEFINED
		&& ((*token)->type != TOKEN
		|| (*token)->id != NEWLINE
		|| (*token)->len > 1))
		return ;
	clean_end_token(&(*token)->prev, head);
	if ((*token)->prev)
		(*token)->prev->next = NULLTOKEN;
	if (*token == *head)
		*head = NULLTOKEN;
	ft_memset(*token, 0, sizeof(**token));
	free(*token);
	*token = NULLTOKEN;
}

static t_token	*handle_new_tokens(t_param *param, t_call *token)
{
	t_param		nparam;


	nparam.e = param->e;
	if (!(nparam.token = new_token(buff, 0)))
		return (NULLTOKEN);
	nparam.token->quoted = param->token->quoted;
	nparam.token->quote = param->token->quote;
	nparam.buff = buff;
	nparam.i = 0;
	nparam.head = nparam.token;
	while (nparam.token->quote)
	{
		
	}
	token_loop(&param, ft_isnull));

}

t_token			*handle_end_of_input(t_param *param, t_call *token)
{
	param->token->len = (param->buff + param->i) - param->token->head;
	if (param->token->type != UNDEFINED && (param->token->id != COMMENT))
		param->token = token[param->token->type].identifier(param);
	clean_end_token(&param->token, &param->head);
	if (param->token->quote)
		return (handle_new_tokens(param, token));
	return (NULLTOKEN);
}
