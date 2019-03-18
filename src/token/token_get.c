/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:20:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/18 17:49:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token_error.h"
#include "token.h"

static t_token	*get_tokens(t_param *param, t_call *token)
{
	static t_func	character[] = {
		CHAR_QUOTE, CHAR_COMMENT, CHAR_EQUAL,
		CHAR_MINUS, CHAR_OPERATOR, CHAR_WORD,
	};
	size_t			i;
	size_t			size;

	i = 0;
	size = (param->token->quote) ? 1 : sizeof(character) / sizeof(character[0]);
	if (param->token->type == UNDEFINED)
		param->token->head = param->line + param->i;
	while (i < size)
	{
		if (character[i].is(param->line[param->i]))
			return (character[i].handler(param, token));
		i++;
	}
	if (!param->token->quote && param->token->type != UNDEFINED)
		return (token[param->token->type].identifier(param));
	return (param->token);
}

t_token			*token_loop(t_param *param, int (*ft_end)(int c))
{
	static t_call	token[] = {
		ID_TOKEN, ID_OPERATOR,
	};

	while (param->token)
	{
		if (ft_isnull(param->line[param->i])
		|| ft_end(param->line[param->i]))
			param->token = handle_end_of_input(param, token);
		else if (quote_type(param->token->quote) == BACKSLASH)
			quote_remove(&param->token->quote, BACKSLASH);
		else
			param->token = get_tokens(param, token);
		param->i++;
	}
	debug_tokens(param->head);
	return (param->head);
}

t_token			*tokenise(char *line, t_s_env *e)
{
	t_param		param;

	ft_memset(&param, 0, sizeof(param));
	param.e = e;
	if (!(param.token = new_token(line, 0)))
		return (token_error(ERR_MALLOC, &param));
	param.line = line;
	param.i = 0;
	param.head = param.token;
	return (token_loop(&param, ft_isnull));
}
