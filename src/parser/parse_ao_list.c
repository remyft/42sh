/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ao_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:43:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/21 02:32:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				parse_ao_list(t_token *token, t_p_param *param)
{
	if ((*param->aolist)->cmd == NULLCOMMAND)
		return (0);
	if (!(param->aolist = new_ao_list(token, &(*param->aolist)->next)))
		return (0);
	if (!(param->cmd = new_command(&(*param->aolist)->cmd)))
		return (0);
	param->arg = &((t_command *)*param->cmd)->args;
	param->redir = &((t_command *)*param->cmd)->redir;
	return (1);
}
