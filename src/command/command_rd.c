/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 19:30:43 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/22 19:56:01 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_env.h"
#include "shell_lib.h"
#include <command.h>
#include <command_error.h>

static void		insert_rd(t_jobs *job, t_prd *new)
{
	t_prd	*r;

	if (!job->rd)
		job->rd = new;
	else
	{
		r = job->rd;
		while (r->next)
			r = r->next;
		r->next = new;
	}
}

int		command_rd(t_s_env *e, t_jobs *job, void *cmd)
{
	t_prd			*new;

	if (!(new = ft_memalloc(sizeof(t_prd))))
		return (command_error(e->progname, ERR_MALLOC, NULL, e));
	new->next = NULL;
	new->rd = (t_redirection *)cmd;
	insert_rd(job, new);
	return (0);
}
