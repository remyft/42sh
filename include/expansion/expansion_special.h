/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_special.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 22:26:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/04 02:58:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_SPECIAL_H
# define EXPANSION_SPECIAL_H

# include "expansion.h"

typedef struct	s_special
{
	const char	value;
	int			(*handler)(t_ret *, t_ret *, t_exp *);
}				t_special;

int				special_argv(t_ret *sub, t_ret *to, t_exp *param);
int				special_argvs(t_ret *sub, t_ret *to, t_exp *param);
int				special_argc(t_ret *sub, t_ret *to, t_exp *param);
int				special_return(t_ret *sub, t_ret *to, t_exp *param);
int				special_option(t_ret *sub, t_ret *to, t_exp *param);
int				special_pid(t_ret *sub, t_ret *to, t_exp *param);
int				special_jobs(t_ret *sub, t_ret *to, t_exp *param);
int				special_error(int error, char *save);

#endif
