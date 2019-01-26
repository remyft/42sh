/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 06:04:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/25 06:25:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"

int				check_command(t_execute *exec, t_s_env *e)
{
	static t_builtins	builtins[] = {
		BUILTIN_ECHO, BUILTIN_CD, BUILTIN_SETENV, BUILTIN_UNSETENV, BUILTIN_ENV,
		BUILTIN_EXIT,
	};
	size_t				i;

	i = 0;
	return (fork_command(exec, e));
}
