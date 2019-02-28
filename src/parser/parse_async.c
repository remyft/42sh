/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_async.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 22:19:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/27 22:39:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				parse_async(t_token **token, t_p_param *param, t_s_env *e)
{
	t_command	*cmd;

	cmd = (t_command *)*param->cmd;
	if (!cmd || !cmd->args)
		return (parse_error(ERR_UNEXPECTED_TOKEN, *token, e));
	cmd->args->async = 1;
	return (1);
}
