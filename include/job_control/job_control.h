/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:09:06 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/30 11:36:42 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include "libft.h"
# include "shell_env.h"
# include "command.h"

# define JOB_TERMINATED 1

enum
{
	STATUS_FINISHED = 1,
	STATUS_RUNNING,
	STATUS_SUSPENDED,
	STATUS_CONTINUED,
	STATUS_TERMINATED,
};

enum
{
	PIPED = 1 << 0,
	AND = 1 << 1,
	OR = 1 << 2,
	END_OF_PIPE = 1 << 3,
};

enum
{
	FD_PIPE_IN = 0,
	FD_PIPE_OUT,
	FD_STDIN,
	FD_STDOUT,
	FD_STDERR
};

# define STR_RUNNING "running"
# define STR_SUSPENDED "suspended"
# define STR_FINISHED "finished"
# define STR_CONTINUE "continued"
# define STR_TERMINATED "terminated"

void			job_handler(t_jobs *job, t_s_env *e);
void			remove_job(t_jobs **jobs, int id);

t_jobs			*job_insert(t_s_env *e);
int				job_wait(t_jobs *job);
int				job_kill(t_jobs *job, t_s_env *e);
int				job_background(t_jobs *job, int cont);
int				job_foreground(t_jobs *job, t_s_env *e, int cont);
int				job_finished(t_jobs *job);
int				jobs_terminated(t_s_env *e);
int				job_completed(t_jobs *job);

t_jobs			*job_by_id(int id, t_jobs *jobs);
t_jobs			*job_by_pid(t_s_env *e, pid_t pid);

int				create_process(t_s_env *e, t_execute *exec, int type);
void			process_status(t_jobs *job, t_m_process *m_p, t_process *p);
int				proc_update(t_s_env *e, t_jobs *job, pid_t pid, int status);

#endif
