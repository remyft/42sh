/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 06:26:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/19 21:46:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "command.h"
#include "shell_env.h"
#include "shell_term.h"

static int		echo_error(t_s_env *e)
{
	ft_dprintf(STDERR_FILENO, "%s: echo: write error: "
	"bad file descriptor\n", e->progname);
	return (1);
}

int				builtin_echo(t_execute *exec, t_s_env *e)
{
	int			i;
	int			j;
	int			n;

	i = 1;
	n = 0;
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
		if (ft_dprintf(STDOUT_FILENO, "%s", exec->cmd[i]) < 0)
			return (echo_error(e));
		else if (exec->cmd[++i] && ft_dprintf(STDOUT_FILENO, " ") < 0)
			return (echo_error(e));
	if (!n && ft_dprintf(STDOUT_FILENO, "\n") < 0)
		return (echo_error(e));
	else if (n)
		{
			tputs(tgetstr("mr", NULL), 1, ft_pchar);
			tputs("%", 1, ft_pchar);
			tputs(tgetstr("me", NULL), 1, ft_pchar);
			tputs("\n", 1, ft_pchar);
		}
	return (0);
}
