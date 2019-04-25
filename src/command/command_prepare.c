/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 20:44:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/24 13:52:17 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "command.h"
#include "command_error.h"
#include "job_control.h"
#include "operator_types.h"

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
			if ((ptr = sh_getnenvaddr(var->cmd[i], e->public_env))
				|| (ptr = sh_getnenvaddr(var->cmd[i], e->private_env)))
				free(*ptr);
			else if (!(ptr = sh_newenv(&e->private_env)))
				return (1);
			*equal = '=';
			*ptr = var->cmd[i];
			var->cmd[i] = NULL;
			i++;
		}
		var = var->next;
	}
	return (0);
}

int				command_prepare(t_execute *exec, t_s_env *e, int type)
{
	t_argument	*ptr;

	ptr = exec->variable;
	while (ptr && ptr->token && ptr->token->id == ASSIGNMENT_WORD)
		ptr = ptr->next;
	exec->command = ptr;
	if (exec->variable != exec->command && !exec->command)
		return (modify_public_environment(exec->variable, e));
	if (!(exec->cmd = command_group_command(exec->command)))
		return (command_error(e->progname, ERR_MALLOC, NULL, e));
	sh_setenv("_", exec->cmd[0], &e->public_env);
	if (!(exec->env = command_group_env(exec->variable, exec->command,
	(const char **)e->public_env, (const char **)e->private_env)))
		return (command_error(e->progname, ERR_MALLOC, exec->cmd, e));
	if (!(create_process(e, exec, type)))
		return (command_error(e->progname, ERR_MALLOC, exec->cmd, e));
	return (0);
}
