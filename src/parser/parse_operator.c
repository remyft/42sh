/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:42:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/12 18:42:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operator_types.h"
#include "parser_errors.h"
#include "parser.h"

static int	add_heredoc(t_p_param *param, t_s_env *e)
{
	t_hdoc	**last;

	last = &param->heredoc;
	while (*last)
		last = &(*last)->next;
	if (!(*last = ft_memalloc(sizeof(**last))))
		return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	(*last)->redir = *param->redir;
	(*last)->head = (*param->redir)->arg->token->head;
	(*last)->len = (*param->redir)->arg->token->len;
	return (1);
}

int			parse_operator(t_token **token, t_p_param *param, t_s_env *e)
{
	if (*param->redir == NULLREDIR)
		if (!(*param->redir = ft_memalloc(sizeof(**param->redir))))
			return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	(*param->redir)->token = *token;
	if ((*token)->next == NULL)
		return (parse_error(ERR_UNEXPECTED_TOKEN, (*token)->next, e));
	if (!((*param->redir)->arg = ft_memalloc(sizeof(*(*param->redir)->arg))))
		return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	*token = (*token)->next;
	(*param->redir)->arg->token = *token;
	if ((*token)->type != TOKEN
		|| ((*token)->id != WORD && (*token)->id != NAME))
		return (parse_error(ERR_UNEXPECTED_TOKEN, *token, e));
	(*token)->id = 0;
	if ((*param->redir)->token->id == DLESS_VALUE)
		if (!add_heredoc(param, e))
			return (0);
	param->redir = &(*param->redir)->next;
	return (1);
}
