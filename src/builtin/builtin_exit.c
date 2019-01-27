/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:42:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 18:51:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"

static int		str_full_digit(const char *s)
{
	size_t		i;

	i = 0;
	if (*s == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
		if (!ft_isdigit(s[i++]))
			return (0);
	return (1);
}

static int		exit_error(int err, const char *cmdname, const char *progname)
{
	static char	*errors[] = {
		"too many arguments", "numeric argument required",
	};
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmdname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(errors[err], STDERR_FILENO);
	return (1);
}

int				builtin_exit(t_execute *exec, t_s_env *e)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (exec->cmd[1])
	{
		if (exec->cmd[2])
			return (exit_error(1, exec->cmd[0], e->progname));
		if (!str_full_digit(exec->cmd[1]))
			return (exit_error(1, exec->cmd[0], e->progname));
	}
	return ((exec->cmd[1]) ? ft_atoi(exec->cmd[1]) : e->ret);
}
