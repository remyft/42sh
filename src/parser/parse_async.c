/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_async.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 22:19:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/10 19:49:24 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_async(void *cmd)
{
	if (!cmd)
		return ;
	if (*(int *)cmd == IS_A_PIPE)
	{
		if (((t_pipeline *)cmd)->left)
			((t_command *)((t_pipeline *)cmd)->left)->async = 1;
		return (set_async(((t_pipeline *)cmd)->right));
	}
	else
		((t_command *)cmd)->async = 1;
}

int				parse_async(t_token **token, t_p_param *param, t_s_env *e)
{
	(*param->list)->async = 1;
	set_async((*param->aolist)->cmd);
	return (parse_list(token, param, e));
}
