/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/20 19:40:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_lib.h"
#include "execution.h"

static int		modify_public_environment(t_argument *var, t_s_env *e)
{
	char		**ptr;
	char		*equal;
	size_t		i;

	while (var)
	{
		i = 0;
		while (var->cmd[i])
		{
			equal = ft_strchr(var->cmd[i], '=');
			*equal = '\0';
			if ((ptr = exp_getnenvaddr(var->cmd[i], e->public_env)))
				free(*ptr);
			else if (!(ptr = exp_newenv(&e->public_env)))
				return (1);
			*equal = '=';
			*ptr = var->cmd[i];
			var->cmd[i] = NULL;
			i++;
		}
		var = var->next;
	}
	for (int i=0; e->public_env[i];i++)
		ft_putendl(e->public_env[i]);
	return (0);
}

int				parse_command(const char *buff, void *cmd, t_s_env *e)
{
	t_argument	*variable;
	t_argument	*command;
	t_argument	*ptr;

	if (!((t_command *)cmd)->args)
		return (0);
	variable = (((t_command *)cmd)->args->token->id == ASSIGNMENT_WORD) ?
				((t_command *)cmd)->args : NULLARG;
	if ((ptr = variable))
		while (ptr->next && ptr->next->token->id == ASSIGNMENT_WORD)
			ptr = ptr->next;
	command = (ptr) ? ptr->next : ((t_command *)cmd)->args;
	debug_execution(cmd);
	if (!variable && !command)
		return (0);
	if (variable && !command)
		return (modify_public_environment(variable, e));
	return (execute_command(buff, variable, command, e));
}

