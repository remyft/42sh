/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 20:44:25 by gbourgeo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/02/23 16:28:44 by dbaffier         ###   ########.fr       */
=======
/*   Updated: 2019/02/21 19:28:53 by gbourgeo         ###   ########.fr       */
>>>>>>> ae67f43beccf4176e735b3f1aabc8424f9d8a5a7
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "command.h"
#include "command_error.h"

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

int				command_prepare(t_execute *exec, t_s_env *e)
{
	t_argument			*ptr;

	ptr = exec->variable;
	while (ptr && ptr->token->id == ASSIGNMENT_WORD)
		ptr = ptr->next;
	exec->command = ptr;
	if (exec->variable != exec->command && !exec->command)
		return (modify_public_environment(exec->variable, e));
	if (!(exec->env = command_group_env(exec->variable, exec->command,
	(const char **)e->public_env, (const char **)e->private_env)))
		return (command_error(e->progname, ERR_MALLOC_VAL, exec->cmd));
	if (!(exec->cmd = command_group_command(exec->command)))
		return (command_error(e->progname, ERR_MALLOC_VAL, NULL));
	return (command_check(exec, e));
}
