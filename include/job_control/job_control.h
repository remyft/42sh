/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:09:06 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/02 15:39:34 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include "libft.h"
# include "shell_env.h"

# define JOB_TERMINATED 1

# define STR_RUNNING "running"
# define STR_SUSPENDED "suspended"
# define STR_DONE "done"
# define STR_CONTINUE "continued"
# define STR_TERMINATED "terminated"


int				job_insert(t_s_env *e, char **cmd);
int				job_by_pid(t_s_env *e, pid_t pid);
int				jobs_terminated(t_s_env *e);
int				job_completed(t_jobs *jobs, int job_id);

t_jobs			*get_job_by_id(int id, t_jobs *jobs);

#endif
