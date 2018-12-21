/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:24:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/21 02:32:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operator.h"
#include "parser.h"

t_m_list		**new_m_list(t_token *token, t_m_list **list)
{
	if (!token || token->type == UNDEFINED)
		return (NULL);
	if ((*list = ft_memalloc(sizeof(**list))) == NULLLIST)
		return (NULL);
	if (token->spec == BACKGRND)
		(*list)->mode = token->spec;
	else
		(*list)->mode = SEMI;
	return (list);
}

t_ao_list		**new_ao_list(t_token *token, t_ao_list **list)
{
	if ((*list = ft_memalloc(sizeof(**list))) == NULLAOLIST)
		return (NULL);
	if (token->spec == OR_IF || token->spec == AND_IF)
		(*list)->mode = token->spec;
	return (list);
}

void			**new_command(void **cmd)
{
	if ((*cmd = ft_memalloc(sizeof(t_command))) == NULL)
		return (NULL);
	((t_command *)(*cmd))->type = IS_A_COMMAND;
	return (cmd);
}

int				new_tree(t_token *token, t_p_param *param, t_m_list **list)
{
	if (!(param->list = new_m_list(token, list)))
		return (0);
	if (!(param->aolist = new_ao_list(token, &(*list)->aolist)))
		return (0);
	if (!(param->cmd = new_command(&(*list)->aolist->cmd)))
		return (0);
	param->arg = &((t_command *)*param->cmd)->args;
	param->redir = &((t_command *)*param->cmd)->redir;
	return (1);
}
