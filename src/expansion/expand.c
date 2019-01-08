/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:18:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/08 01:18:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

static int		check_redirect(const char *buff, t_redirection *cmd, t_s_env *e)
{
	if (!cmd)
		return (0);
	if (expand_argument(buff, cmd->arg, e))
		return (1);
//	redirection(buff, cmd);
	return (check_redirect(buff, cmd->next, e));
}

static int		check_command_type(const char *buff, void *cmd, t_s_env *e)
{
	if (!cmd)
		return (0);
	if (*(int *)cmd == IS_A_PIPE)
		return (check_command_type(buff, ((t_pipeline *)cmd)->left, e)
			|| check_command_type(buff, ((t_pipeline *)cmd)->right, e));
	return (expand_argument(buff, ((t_command *)cmd)->args, e)
		|| check_redirect(buff, ((t_command *)cmd)->redir, e));
}

static int		check_ao_list(const char *buff, t_ao_list *aolist, t_s_env *e)
{
	if (!aolist)
		return (0);
	if (check_command_type(buff, aolist->cmd, e))
		return (1);
//	execute_command(buff, aolist->cmd, e);
	return (check_ao_list(buff, aolist->next, e));
}

int				expand(const char *buff, t_m_list *list, t_s_env *e)
{
	if (!list)
		return (0);
	if (check_ao_list(buff, list->aolist, e))
		return (1);
	return (expand(buff, list->next, e));
}
