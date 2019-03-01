/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/01 18:36:48 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"
#include "job_insert.h"
#include "command_error.h"

int				command_parse(void *cmd, t_s_env *e)
{
	t_execute	exec;

	if (*(int *)cmd == IS_A_PIPE)
		return (command_pipe(cmd, e, (int [2]){ 0, 0 }));
	command_debug(cmd);
	ft_memset(&exec, 0, sizeof(exec));
	if (!((t_command *)cmd)->args)
		return (0);
	exec.variable = ((t_command *)cmd)->args;
	exec.redirection = ((t_command *)cmd)->redir;

	t_argument			*ptr;

	ptr = exec.variable;
	while (ptr && ptr->token->id == ASSIGNMENT_WORD)
		ptr = ptr->next;
	if (!(exec.job_id = job_insert(e, ptr->cmd)))
		return (command_error(e->progname, ERR_MALLOC_VAL, NULL));
	return (command_prepare(&exec, e));
}
