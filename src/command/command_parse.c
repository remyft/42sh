/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/22 18:50:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main_tools.h"
#include "shell.h"
#include "command.h"

int				command_parse(void *cmd, t_s_env *e)
{
	t_execute	exec;
	int			ret;

	ft_memset(&exec, 0, sizeof(exec));
	if (!e->forked)
		term_restore(e->save);
	if (*(int *)cmd == IS_A_PIPE)
		ret = command_pipe(cmd, e, (int[2]){ 0, 0 });
	else
	{
		command_debug(cmd);
		if (!((t_command *)cmd)->args)
			return (0);
		exec.variable = ((t_command *)cmd)->args;
		exec.redirection = ((t_command *)cmd)->redir;
		ret = command_prepare(&exec, e);
	}
	if (!e->forked)
		define_new_term(&e->save);
	command_free(&exec, NULL);
	return (ret);
}
