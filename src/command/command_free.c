/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 15:24:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/03 17:51:50 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <stdlib.h>
#include <stdio.h>

void		command_free(t_execute *exec, char *name)
{
	if (exec->env)
		free(exec->env);
	exec->env = NULL;
	if (exec->cmd)
		free(exec->cmd);
	exec->cmd = NULL;
	if (name)
		;
	//	free(name);
	if (exec)
		free(exec);
}
