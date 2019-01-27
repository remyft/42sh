/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 14:05:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "execution.h"
#include "execution_error.h"
#include "builtins.h"

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

static int		command_builtin(int (*builtin)(t_execute *, t_s_env *),
t_execute *exec, t_s_env *e)
{
	if (exec->variable == exec->command)
		exec->env = e->public_env;
	else if (!(exec->env = duplicate_environ(e->public_env))
		|| !(exec->env = modify_environ(exec->variable, exec)))
		return (command_error(e->progname, ERR_MALLOC_VAL, exec->cmd));
	e->ret = builtin(exec, e);
	command_free(exec, e->public_env, NULL);
	return (0);
}

static int		command_normal(t_execute *exec, t_s_env *e)
{
	static t_builtins	builtins[] = {
		BUILTIN_ECHO, BUILTIN_CD, BUILTIN_SETENV,/* BUILTIN_UNSETENV, BUILTIN_ENV,
		BUILTIN_EXIT,*/
	};
	size_t				i;
	t_argument			*ptr;

	ptr = exec->variable;
	while (ptr && ptr->token->id == ASSIGNMENT_WORD)
		ptr = ptr->next;
	exec->command = ptr;
	if (exec->variable != exec->command && !exec->command)
		return (modify_public_environment(exec->variable, e));
	if (!(exec->cmd = command_group(exec->command)))
		return (command_error(e->progname, ERR_MALLOC_VAL, NULL));
	i = 0;
	while (i < sizeof(builtins) / sizeof(builtins[0]))
	{
		if (!ft_strcmp(builtins[i].name, exec->cmd[0]))
			return (command_builtin(builtins[i].handler, exec, e));
		i++;
	}
	return (command_fork(exec, e));
}

static int		command_pipe(t_execute *exec, t_s_env *e)
{
	exec->piped = 1;
	return (command_fork(exec, e));
}

int				command_parse(void *cmd, t_s_env *e)
{
	t_execute	exec;

	debug_execution(cmd);
	ft_memset(&exec, 0, sizeof(exec));
	if (!((t_command *)cmd)->args)
		return (0);
	exec.variable = ((t_command *)cmd)->args;
	exec.redirection = ((t_command *)cmd)->redir;
	if (*(int *)cmd == IS_A_PIPE)
		return (command_pipe(&exec, e));
	return (command_normal(&exec, e));
}
