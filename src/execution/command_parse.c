/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/25 15:12:55 by rfontain         ###   ########.fr       */
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
			if ((ptr = exp_getnenvaddr(var->cmd[i], e->public_env))
				|| (ptr = exp_getnenvaddr(var->cmd[i], e->private_env)))
				free(*ptr);
			else if (!(ptr = exp_newenv(&e->private_env)))
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

static int		normal_command(t_execute *exec, t_s_env *e)
{
	t_argument	*ptr;

	ptr = exec->variable;
	while (ptr && ptr->token->id == ASSIGNMENT_WORD)
		ptr = ptr->next;
	exec->command = ptr;
	if (exec->variable != exec->command && !exec->command)
		return (modify_public_environment(exec->variable, e));
	return (fork_command(exec, e));
}

static int		pipe_command(t_execute *exec, t_s_env *e)
{
	exec->piped = 1;
	return (fork_command(exec, e));
}

int				parse_command(void *cmd, t_s_env *e)
{
	t_execute	exec;

	debug_execution(cmd);
	ft_memset(&exec, 0, sizeof(exec));
	if (!((t_command *)cmd)->args)
		return (0);
	exec.variable = ((t_command *)cmd)->args;
	exec.redirection = ((t_command *)cmd)->redir;
	if (*(int *)cmd == IS_A_PIPE)
		return (pipe_command(&exec, e));
	return (normal_command(&exec, e));
}
