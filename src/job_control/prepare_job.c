/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_job.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:13:28 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/04 17:17:36 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job_control.h"
#include "operator_types.h"
#include "command.h"
#include "expansion.h"

static int	job_in(t_argument *ptr, t_s_env *e)
{
	char			**test;

	while (ptr && ptr->token->id == ASSIGNMENT_WORD)
		ptr = ptr->next;
	//printf("%s\n", ptr->cmd[0]);
	test = command_group_command(ptr);
	//printf("Hey\n");
	(void)e;
	return (1);
}

static int	prepare_job(void *cmd, t_s_env *e)
{
	if (!cmd)
		return (0);
	if (*(int *)cmd == IS_A_PIPE)
		// after
		;
	else if (expand_argument(((t_command *)cmd)->args, e) || job_in(((t_command *)cmd)->args, e))
		return (1);
	return (0);
}

static int jobs_ao_parse(t_ao_list *aolist, t_s_env *e)
{
	if (!aolist)
		return (0);
	if (!aolist->type
		|| (aolist->type == OR_IF_VALUE && e->ret)
		|| (aolist->type == AND_IF_VALUE && !e->ret))
	{
		if (prepare_job(aolist->cmd, e))
			return (1);
	}
	return (jobs_ao_parse(aolist->next, e));
}

int		jobs_prepare(t_m_list *list, t_s_env *e)
{
	if (!list)
		return (0);
	if (jobs_ao_parse(list->aolist, e))
		return (1);
	return (jobs_prepare(list->next, e));
}
