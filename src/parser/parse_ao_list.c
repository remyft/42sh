/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ao_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:43:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/20 20:43:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				parse_ao_list(t_token *token, t_p_param *param)
{
	if ((*param->aolist)->cmd == NULLCOMMAND)
		return (1);
	if (!(param->aolist = new_ao_list(token, &(*param->aolist)->next)))
		return (1);
	if (!(param->cmd = new_command(&(*param->aolist)->cmd)))
		return (1);
	param->arg = &((t_command *)*param->cmd)->args;
	param->redir = &((t_command *)*param->cmd)->redir;
	return (0);
}
