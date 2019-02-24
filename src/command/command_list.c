/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 02:19:16 by gbourgeo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/02/24 17:47:26 by dbaffier         ###   ########.fr       */
=======
/*   Updated: 2019/02/24 18:56:20 by gbourgeo         ###   ########.fr       */
>>>>>>> 0da62b1aea1eb542d11da9bd1755dd461c2b81ca
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"
#include "operator_types.h"
#include "expansion.h"
#include "redirection.h"

static int	redirect_prepare(t_redirection *cmd, t_s_env *e)
{
	if (!cmd)
		return (0);
	if (cmd->arg)
	{
		if (expand_argument(cmd->arg, e))
			return (1);
		quote_removal(cmd->arg);
	}
	if (cmd->token)
		if (redirection(&cmd, e))
			return (1);
	return (redirect_prepare(cmd->next, e));
}

static int	prepare_command(void *cmd, t_s_env *e)
{
	if (!cmd)
		return (0);
	if (*(int *)cmd == IS_A_PIPE)
		return (prepare_command(((t_pipeline *)cmd)->left, e)
				|| prepare_command(((t_pipeline *)cmd)->right, e));
	else if (expand_argument(((t_command *)cmd)->args, e)
		|| redirect_prepare(((t_command *)cmd)->redir, e))
		return (1);
	quote_removal(((t_command *)cmd)->args);
	return (0);
}

static int	execute_ao_list(t_ao_list *aolist, t_s_env *e, int mode)
{
	if (!aolist)
		return (0);
<<<<<<< HEAD
	if (mode & BACKGRND_VALUE)
	{
		printf("Enter\n");
		//execute_backgrnd_list(aolist->cmd, e);
	}
=======
	if (!aolist->next && mode == BACKGRND_VALUE)
		ft_putendl("BACKGROUND !");
>>>>>>> 0da62b1aea1eb542d11da9bd1755dd461c2b81ca
	if (!aolist->mode
		|| (aolist->mode == OR_IF_VALUE && e->ret)
		|| (aolist->mode == AND_IF_VALUE && !e->ret))
		if (prepare_command(aolist->cmd, e)
			|| command_parse(aolist->cmd, e))
			return (1);
	return (execute_ao_list(aolist->next, e, mode));
}

int			execute_list(t_m_list *list, t_s_env *e)
{
	if (!list)
		return (0);
	if (execute_ao_list(list->aolist, e, list->mode))
		return (1);
	return (execute_list(list->next, e));
}
