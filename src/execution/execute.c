/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 02:19:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/14 00:27:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "operator_types.h"
#include "expansion.h"

static int		check_redirect(const char *buff, t_redirection *cmd, t_s_env *e)
{
	if (!cmd)
		return (0);
	if (expand_argument(buff, cmd->arg, e))
		return (1);
	quote_removal(cmd->arg);
	return (check_redirect(buff, cmd->next, e));
}

static void		parse_cmd(t_argument **var, t_argument **com, t_argument *args)
{
	t_argument	*ptr;

	*var = (args->token->id == ASSIGNMENT_WORD) ? args : NULLARG;
	ptr = args;
	while (ptr && ptr->token->id == ASSIGNMENT_WORD)
		ptr = ptr->next;
	*com = ptr;
}

static int		check_command_type(const char *buff, void *cmd, t_s_env *e)
{
	t_argument	*variable;
	t_argument	*command;

	if (!cmd)
		return (0);
	if (*(int *)cmd == IS_A_PIPE)
		return (check_command_type(buff, ((t_pipeline *)cmd)->left, e)
			|| check_command_type(buff, ((t_pipeline *)cmd)->right, e));
	if (expand_argument(buff, ((t_command *)cmd)->args, e)
		|| check_redirect(buff, ((t_command *)cmd)->redir, e))
		return (1);
	quote_removal(((t_command *)cmd)->args);
	debug_execution(cmd);
	parse_cmd(&variable, &command, ((t_command *)cmd)->args);
	return (exec_command(buff, cmd, e));
}

static int		check_ao_list(const char *buff, t_ao_list *aolist, t_s_env *e)
{
	if (!aolist)
		return (0);
	if (!aolist->mode
		|| (aolist->mode == OR_IF_VALUE && e->ret)
		|| (aolist->mode == AND_IF_VALUE && !e->ret))
		if (check_command_type(buff, aolist->cmd, e))
			return (1);
	return (check_ao_list(buff, aolist->next, e));
}

int				execute(const char *buff, t_m_list *list, t_s_env *e)
{
	if (!list)
		return (0);
	if (check_ao_list(buff, list->aolist, e))
		return (1);
	return (execute(buff, list->next, e));
}
