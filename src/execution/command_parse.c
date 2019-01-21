/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/21 23:22:08 by gbourgeo         ###   ########.fr       */
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
			*(equal = ft_strchr(var->cmd[i], '=')) = '\0';
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

// static int	pipe_command(const char *buff, void *cmd, t_s_env *e)
// {
// 	(void)buff;
// 	(void)cmd;
// 	(void)e;
// 	return (0);
// }

int				parse_command(const char *buff, void *cmd, t_s_env *e, int var)
{
	t_execute	exec;
	t_argument	*ptr;

	ft_memset(&exec, 0, sizeof(exec));
	if (!((t_command *)cmd)->args)
		return (0);
	// if (*(int *)cmd == IS_A_PIPE)
		(void)var;
	exec.variable = ((t_command *)cmd)->args;
	ptr = exec.variable;
	while (ptr && ptr->token->id == ASSIGNMENT_WORD)
		ptr = ptr->next;
	exec.command = ptr;
	debug_execution(cmd);
	if (!exec.variable && !exec.command)
		return (0);
	if (exec.variable != exec.command && !exec.command)
		return (modify_public_environment(exec.variable, e));
	return (execute_command(buff, &exec, e));
}

