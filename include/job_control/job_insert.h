/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_insert.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 22:12:48 by dbaffier          #+#    #+#             */
/*   Updated: 2019/02/28 15:31:42 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_INSERT_H
# define JOB_INSERT_H

# include "shell_env.h"

int			job_insert(t_s_env *e, char **cmd);
t_jobs		*get_job_by_id(int id, t_jobs *jobs);

#endif
