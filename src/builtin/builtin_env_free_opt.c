/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_free_opt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 11:25:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/02 20:27:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "builtin_env.h"
#include "shell_lib.h"

void				env_free_opt(t_e_opt *opt)
{
	sh_freetab(&opt->env);
	sh_freestr(&opt->cmd);
}
