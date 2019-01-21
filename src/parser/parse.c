/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:00:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/19 01:13:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "handler.h"

static int		parse_not_handled_yet(const char *buff, t_token **token,
t_p_param *param)
{
	(void)buff;
	(void)token;
	(void)param;
	return (0);
}

static int		parse_loop(const char *buff, t_token *token, t_p_param *param)
{
	static t_p_call		type_token[] = {
		H_ARGUMENT, H_ARGUMENT, H_ARGUMENT, { NULL }, H_IO_NUMBER,
		H_ARGUMENT,
	};
	static t_p_call		type_operator[] = {
		{ NULL }, H_AO_LIST, H_PIPE, H_OPERATOR, { NULL }, H_AO_LIST,
		H_LIST, H_LIST, H_ERROR, H_OPERATOR, H_OPERATOR, H_OPERATOR,
		H_OPERATOR, H_OPERATOR, H_OPERATOR, H_OPERATOR, H_OPERATOR,
		H_OPERATOR, H_OPERATOR, H_OPERATOR, H_OPERATOR,
	};
	static t_t_p_call	call[] = {
		{ type_token }, { type_operator },
	};

	while (token)
	{
		if (token->type != UNDEFINED
			&& call[token->type].type[token->id].handler
			&& !call[token->type].type[token->id].handler(buff, &token, param))
			return (0);
		token = token->next;
	}
	return (1);
}

t_m_list		*parse(const char *buff, t_token *token)
{
	t_m_list	*list;
	t_p_param	param;

	if ((!new_tree(token, &param, &list) && !parse_error(buff, token))
		|| !parse_loop(buff, token, &param))
		free_m_list(&list);
	else
		debug_parser(buff, list);
	return (list);
}
