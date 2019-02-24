/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:09:06 by dbaffier          #+#    #+#             */
/*   Updated: 2019/02/24 17:39:35 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

typedef struct			s_process
{
	pid_t		pid;
	int			status;
}						t_process;

typedef struct			s_jobs
{
	t_process			*proc;
	pid_t				pgid;
	struct s_jobs		*next;
}						t_jobs;

#endif
