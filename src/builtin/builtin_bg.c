/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 13:38:06 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/23 10:04:34 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "builtin_jobs.h"
#include "builtins.h"

static int		bg(const t_jobs *jobs, t_s_env *e)
{
	return (job_background((t_jobs *)jobs, e, 1));
}

static int		bg_no_arg(t_s_env *e, t_execute *exec)
{
	t_jobs		*jobs;
	
	jobs = e->jobs;
	while (jobs)
	{
		if (job_is_curr((t_jobs *)jobs, exec))
			;
		else
			return (bg(jobs, e));
		jobs = jobs->next;
	}
	return (1);
}

static int		bg_spe_arg(t_s_env *e, t_execute *exec, int i)
{
	int		err;
	char	**cmd;
	t_jobs	*curr;

	err = 0;
	cmd = exec->cmd;
	if (!(curr = jobs_expansions(cmd[i], exec, e)))
		return (bg_error(2, cmd[i], e));
	return (bg(curr, e));
}

static int		bg_opts(char **arg, t_s_env *e)
{
	if (arg[1] && arg[1][0] == '-')
		return (bg_error(ERR_INVALID_OPTION, &arg[1][1], e));
	return (0);
}

int		builtin_bg(t_execute *exec, t_s_env *e)
{
	int		i;

	i = 1;
	if (bg_opts(exec->cmd, e))
		return (1);
	if (!exec->cmd[i])
		return (bg_no_arg(e, exec));
	return (bg_spe_arg(e, exec, i));
}
