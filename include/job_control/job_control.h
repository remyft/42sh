/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:09:06 by dbaffier          #+#    #+#             */
/*   Updated: 2019/02/25 17:32:55 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# define JOB_RUNNING "running"
# define JOB_SUSPENDED "suspended"
# define JOB_DONE "done"
# define JOB_CONTINUE "continued"
# define JOB_TERMINATED "terminated"

typedef struct			s_process
{
	int					pid;
	int					status;
	struct s_process	*next;
}						t_process;

typedef struct			s_jobs
{
	t_process			*proc;
	int					pgid;
	struct s_jobs		*next;
}						t_jobs;

#endif
