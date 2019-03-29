/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 02:19:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/26 16:17:39 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job_control.h"
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

static int	parse_type(int type)
{
	if (type == OR_IF_VALUE)
		return (OR);
	else if (type == AND_IF_VALUE)
		return (AND);
	return (0);
}

static int	execute_ao_list(t_ao_list *aolist, t_s_env *e, t_jobs *job)
{
	if (!aolist)
		return (0);
	//	|| (aolist->type == OR_IF_VALUE && e->ret)
		//|| (aolist->type == AND_IF_VALUE && !e->ret))
	//{
	//if (!aolist->type)
	//{
		if (command_m_process(e, job, aolist->type)
			|| prepare_command(aolist->cmd, e)
			|| command_parse(aolist->cmd, e, parse_type(aolist->type)))
			return (1);
	//}
	return (execute_ao_list(aolist->next, e, job));
}

static char		*get_command(t_m_list *list)
{
	t_ao_list	*ao;
	t_command	*cmd;
	t_argument	*arg;
	const char		*head;
	const char		*tail;

	if (!list || !list->aolist || !list->aolist->cmd)
		return (NULL);
	cmd = (t_command *)list->aolist->cmd;
	if (cmd->type == IS_A_PIPE)
		head = ((t_command *)((t_pipeline *)cmd)->left)->args->token->head;
	else
		head = cmd->args->token->head;
	printf("head : %s\n", head);
	ao = list->aolist;
	while (ao->next)
		ao = ao->next;
	cmd = ao->cmd;
	while (cmd->type == IS_A_PIPE)
		cmd = ((t_pipeline *)cmd)->right;
	arg = cmd->args;
	while (arg->next)
		arg = arg->next;
	tail = arg->token->head + arg->token->len;
	printf("tail : %s\n", tail);
	return (ft_strndup((char *)head, tail - head));
}

int			execute_list(t_m_list *list, t_s_env *e)
{
	pid_t	pid;
	char	*s;
	t_jobs	*job;

	s = get_command(list);
	printf("%s\n", s);
	sleep(1);
	exit(1);
	pid = 0;
	if (!list)
		return (0);
	e->async = list->async;
	job = jobs_prepare(e);
	if (execute_ao_list(list->aolist, e, job))
		return (1);
	command_job(job, e);
	return (execute_list(list->next, e));
}
