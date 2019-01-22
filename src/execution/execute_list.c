/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 02:19:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/22 07:46:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "operator_types.h"
#include "expansion.h"
#include "redirection.h"

static int	prepare_redirect(const char *buff, t_redirection *cmd, t_s_env *e)
{
	if (!cmd)
		return (0);
	if (expand_argument(buff, cmd->arg, e))
		return (1);
	quote_removal(cmd->arg);
	if (redirection(buff, cmd, e))
		return (1);
	return (prepare_redirect(buff, cmd->next, e));
}

static int	prepare_command(const char *buff, void *cmd, t_s_env *e)
{

	if (!cmd)
		return (0);
	if (*(int *)cmd == IS_A_PIPE)
		return (prepare_command(buff, ((t_pipeline *)cmd)->left, e)
			|| prepare_command(buff, ((t_pipeline *)cmd)->right, e));
	if (expand_argument(buff, ((t_command *)cmd)->args, e)
		|| prepare_redirect(buff, ((t_command *)cmd)->redir, e))
		return (1);
	quote_removal(((t_command *)cmd)->args);
	return (0);
}

static int	execute_ao_list(const char *buff, t_ao_list *aolist, t_s_env *e)
{
	if (!aolist)
		return (0);
	if (!aolist->mode
		|| (aolist->mode == OR_IF_VALUE && e->ret)
		|| (aolist->mode == AND_IF_VALUE && !e->ret))
		if (prepare_command(buff, aolist->cmd, e)
			|| parse_command(aolist->cmd, e))
			return (1);
	return (execute_ao_list(buff, aolist->next, e));
}

int			execute_list(const char *buff, t_m_list *list, t_s_env *e)
{
	if (!list)
		return (0);
	if (execute_ao_list(buff, list->aolist, e))
		return (1);
	return (execute_list(buff, list->next, e));
}
