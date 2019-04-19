/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 09:06:34 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/19 13:50:52 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "builtin_jobs.h"

int		fg(const t_jobs *jobs, t_s_env *e)
{
	return (job_foreground((t_jobs *)jobs, e, 1));
}


int		fg_no_arg(t_s_env *e, t_execute *exec)
{
	t_jobs		*jobs;

	jobs = e->jobs;
	while (jobs)
	{
		if (job_is_curr((t_jobs *)jobs, exec))
			;
		else
			return (fg(jobs, e));
		jobs = jobs->next;
	}
	return (0);
}

int		fg_spe_arg(t_s_env *e, t_execute *exec, int i)
{
	int		err;
	char	**cmd;
	t_jobs	*curr;

	err = 0;
	cmd = exec->cmd;
	if (!(curr = jobs_expansions(cmd[i], exec, e)))
		return (fg_error(2, cmd[i], e));
	return (fg(curr, e));
}

int		fg_opts(char **arg, t_s_env *e)
{
	if (arg[1] && arg[1][0] == '-')
		return (fg_error(ERR_INVALID_OPTION, &arg[1][1], e));
	return (0);
}

int		builtin_fg(t_execute *exec, t_s_env *e)
{
	int		err;
	int		i;

	i = 1;
	if ((err = fg_opts(exec->cmd, e)) != 0)
		return (err);
	if (!exec->cmd[i])
		return (fg_no_arg(e, exec));
	return (fg_spe_arg(e, exec, i));
}
