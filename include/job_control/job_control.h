/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:09:06 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/09 11:30:18 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include "libft.h"
# include "shell_env.h"
# include "command.h"

# define JOB_TERMINATED 1

enum {
	STATUS_FINISHED = 1,
	STATUS_RUNNING,
	STATUS_SUSPENDED,
	STATUS_CONTINUED,
	STATUS_TERMINATED,
};

# define STR_RUNNING "running"
# define STR_SUSPENDED "suspended"
# define STR_FINISHED "finished"
# define STR_CONTINUE "continued"
# define STR_TERMINATED "terminated"

void			job_handler(t_jobs *job, t_s_env *e);
void			remove_job(t_jobs **jobs, int id);

t_jobs			*job_insert(t_s_env *e);
int				jobs_terminated(t_s_env *e);
int				job_completed(t_jobs *job);

t_jobs			*job_by_id(int id, t_jobs *jobs);
t_jobs			*job_by_pid(t_s_env *e, pid_t pid);

t_process		*create_process(t_execute *exec, t_s_env *e);
int				set_pstatus(t_process *p, int status);
int				proc_update(t_jobs *job, pid_t pid, int status);

#endif
