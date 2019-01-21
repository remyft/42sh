/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/20 02:21:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int		modify_public_environment(t_argument *var, t_s_env *e)
{
	(void)var;
	(void)e;
	return (0);
}

int				parse_command(t_argument *args, t_s_env *e)
{
	t_argument	*variable;
	t_argument	*command;
	t_argument	*ptr;

	if (!args)
		return (0);
	variable = (args->token->id == ASSIGNMENT_WORD) ? args : NULLARG;
	if ((ptr = variable))
		while (ptr->next && ptr->next->token->id == ASSIGNMENT_WORD)
			ptr = ptr->next;
	command = (ptr) ? ptr->next : args;
	if (!variable && !command)
		return (0);
	if (variable && !command)
		return (modify_public_environment(variable, e));
	return (0);
}

