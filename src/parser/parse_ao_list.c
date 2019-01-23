/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ao_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:43:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/23 02:56:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "operator_types.h"

static int	check_token_next(t_token *token)
{
	if (token == NULLTOKEN)
		return (0);
	if (token->type == TOKEN)
		return (1);
	if (token->id < LESS_VALUE)
		return (0);
	return (1);
}

int			parse_ao_list(t_token **token, t_p_param *param)
{
	if (*param->arg == NULLARG && *param->redir == NULLREDIR)
		return (parse_error(*token));
	if (!check_token_next((*token)->next))
		return (parse_error((*token)->next));
	if (!(param->aolist = new_ao_list(*token, &(*param->aolist)->next)))
		return (parse_error(*token));
	if (!(param->cmd = new_command(&(*param->aolist)->cmd)))
		return (parse_error(*token));
	param->arg = &((t_command *)*param->cmd)->args;
	param->redir = &((t_command *)*param->cmd)->redir;
	return (1);
}
