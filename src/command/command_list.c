/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 02:19:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/06 17:01:04 by dbaffier         ###   ########.fr       */
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

static int	execute_ao_list(t_ao_list *aolist, t_s_env *e)
{
	if (!aolist)
		return (0);
	if (!aolist->type
		|| (aolist->type == OR_IF_VALUE && e->ret)
		|| (aolist->type == AND_IF_VALUE && !e->ret))
	{
		if (prepare_command(aolist->cmd, e)
			|| command_parse(aolist->cmd, e))
			return (1);
	}
	return (execute_ao_list(aolist->next, e));
}

static int print_job_status(t_jobs *jobs, int id)
{
	printf("[%d]", id);
    printf("%d", jobs->process->pid);
	printf("\n");
    return (0);
}

int			execute_list(t_m_list *list, t_s_env *e)
{
	pid_t	pid;

	pid = 0;
	if (!list)
		return (0);
	e->async = list->async;
	jobs_prepare(list, e);
	if (list->async)
	{
		t_jobs	*job;
	//	printf("job id[%d]\n", e->job_id);
		job = get_job_by_id(e->job_id, e->jobs);
		e->forked = 1;
		if ((pid = fork()) < 0)
			return (1);
		if (pid == 0)
		{
			execute_ao_list(list->aolist, e);
			exit(0);
		}
	//	waitpid(pid, NULL, 0);
	//	printf("Pid : [%d]\n", pid);
		job->process->pid = pid;
		print_job_status(job, e->job_id);
		e->forked = 0;
	}
	else if (execute_ao_list(list->aolist, e))
		return (1);
	return (execute_list(list->next, e));
}
