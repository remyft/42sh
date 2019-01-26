/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:10:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/26 18:25:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "shell_env.h"

static int		redirect_error(const char *err, t_s_env *e)
{
	ft_putstr_fd(e->progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	return (1);
}

int				command_redirect(t_redirection *redirection, t_s_env *e)
{
	while (redirection)
	{
		if (dup2(redirection->fdarg, redirection->fdio) < 0)
			return (redirect_error("dup2 failed.", e));
		redirection = redirection->next;
	}
	return (0);
}
