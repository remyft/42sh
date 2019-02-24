/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_new_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:24:09 by gbourgeo          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2019/02/23 16:36:52 by dbaffier         ###   ########.fr       */
=======
/*   Updated: 2019/02/22 22:34:37 by gbourgeo         ###   ########.fr       */
>>>>>>> ae67f43beccf4176e735b3f1aabc8424f9d8a5a7
=======
/*   Updated: 2019/02/24 18:01:42 by gbourgeo         ###   ########.fr       */
>>>>>>> 21b2848435b65b265fbd3fb244949ce539f3ea8a
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operator_types.h"
#include "parser.h"

t_m_list		**new_m_list(t_token *token, t_m_list **list)
{
	if (!token || token->type == UNDEFINED)
		return (NULL);
	if ((*list = ft_memalloc(sizeof(**list))) == NULLLIST)
		return (NULL);
	(*list)->mode = SEMI_VALUE;
	return (list);
}

t_ao_list		**new_ao_list(t_token *token, t_ao_list **list)
{
	if ((*list = ft_memalloc(sizeof(**list))) == NULLAOLIST)
		return (NULL);
	if (token->type == OPERATOR
		&& (token->id == OR_IF_VALUE || token->id == AND_IF_VALUE))
		(*list)->mode = token->id;
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
