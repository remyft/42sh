/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 06:26:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/25 06:52:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell_env.h"

static int		builtin_echo_strlen(const char *str)
{
	int			i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int				builtin_echo(char **args, t_s_env *e)
{
	int			i;
	int			j;
	int			n;

	i = 1;
	n = 0;
	(void)e;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		if ((n = (args[i][j] == 'n')))
			while (args[i][j] == 'n')
				j++;
		if (!(n = (args[i][j] == '\0')))
			break ;
		i++;
	}
	while (args[i])
		if (write(STDIN_FILENO, args[i], builtin_echo_strlen(args[i])) < 0)
			return (1);
		else if (args[++i] && write(STDIN_FILENO, " ", 1) < 0)
			return (1);
	if (!n && write(STDIN_FILENO, "\n", 1) < 0)
		return (1);
	return (0);
}
