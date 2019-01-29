/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 06:26:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/26 10:18:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "command.h"
#include "shell_env.h"

static int		echo_strlen(const char *str)
{
	int			i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int				builtin_echo(t_execute *exec, t_s_env *e)
{
	int			i;
	int			j;
	int			n;

	i = 1;
	n = 0;
	(void)e;
	while (exec->cmd[i] && exec->cmd[i][0] == '-' && exec->cmd[i][1])
	{
		j = 1;
		if ((n = (exec->cmd[i][j] == 'n')))
			while (exec->cmd[i][j] == 'n')
				j++;
		if (exec->cmd[i][j] != '\0' && ((i > 1) || !(n = 0)))
			break ;
		i++;
	}
	while (exec->cmd[i])
		if (write(STDIN_FILENO, exec->cmd[i], echo_strlen(exec->cmd[i])) < 0)
			return (1);
		else if (exec->cmd[++i] && write(STDIN_FILENO, " ", 1) < 0)
			return (1);
	if (!n && write(STDIN_FILENO, "\n", 1) < 0)
		return (1);
	return (0);
}
