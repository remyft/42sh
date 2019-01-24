/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 00:59:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/24 07:06:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"
#include "operator_types.h"
#include <sys/syslimits.h>

int				redirect_open_error(char *filename, t_s_env *e)
{
	ft_putstr_fd(e->progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (access(filename, F_OK))
		ft_putstr_fd("no such file or directory: ", STDERR_FILENO);
	else if (ft_strlen(filename) > NAME_MAX)
		ft_putstr_fd("file name too long: ", STDERR_FILENO);
	else
		ft_putstr_fd("permission denied: ", STDERR_FILENO);
	ft_putendl_fd(filename, STDERR_FILENO);
	return (1);
}

int				redirect_error(int err, char *redirect_arg, t_s_env *e)
{
	static char	*error[] = {
		"not enought memory", "ambiguous redirect", "Bad file descriptor",
	};
	ft_putstr_fd(e->progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(redirect_arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error[err], STDERR_FILENO);
	return (1);
}

int				redirect_less(t_redirection **redir, t_s_env *e)
{
	(*redir)->fdio = ((*redir)->ionumber) ? ft_atoi((*redir)->ionumber->head) : 0;
	if (((*redir)->fdarg = open((*redir)->arg->cmd[0], O_RDONLY)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	return (0);
}

int				redirect_less_and(t_redirection **redir, t_s_env *e)
{
	size_t		i;

	i = 0;
	(*redir)->fdio = ((*redir)->ionumber) ? ft_atoi((*redir)->ionumber->head) : 0;
	if (!ft_strcmp((*redir)->arg->cmd[0], "-"))
	{
		if (((*redir)->fdarg = open("/dev/null", O_RDWR)) < 0)
			return (redirect_open_error("/dev/null", e));
		return (0);
	}
	while ((*redir)->arg->cmd[0][i])
		if (!ft_isdigit((*redir)->arg->cmd[0][i]))
			return (redirect_error(ERR_AMBIGUOUS, (*redir)->arg->cmd[0], e));
		else
			i++;
	(*redir)->fdarg = ft_atoi((*redir)->arg->cmd[0]);
	if (fcntl((*redir)->fdarg, F_GETFD) < 0)
		return (redirect_error(ERR_BAD_FD, (*redir)->arg->cmd[0], e));
	return (0);
}

int				redirect_less_great(t_redirection **redir, t_s_env *e)
{
	(*redir)->fdio = ((*redir)->ionumber) ? ft_atoi((*redir)->ionumber->head) : 0;
	if (((*redir)->fdarg = open((*redir)->arg->cmd[0], O_CREAT | O_RDWR, 0644)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	return (0);
}

int				redirect_great(t_redirection **redir, t_s_env *e)
{
	int			mode;

	mode = O_CREAT | O_TRUNC | O_WRONLY;
	(*redir)->fdio = ((*redir)->ionumber) ? ft_atoi((*redir)->ionumber->head) : 1;
	if (((*redir)->fdarg = open((*redir)->arg->cmd[0], mode, 0644)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	return (0);
}

int				redirect_great_pipe(t_redirection **redir, t_s_env *e)
{
	int			mode;

	mode = O_CREAT | O_TRUNC | O_WRONLY;
	(*redir)->fdio = ((*redir)->ionumber) ? ft_atoi((*redir)->ionumber->head) : 1;
	if (((*redir)->fdarg = open((*redir)->arg->cmd[0], mode, 0644)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	return (0);
}

int				redirect_and_great(t_redirection **redir, t_s_env *e)
{
	t_redirection	*next;
	int				mode;

	mode = O_CREAT | O_TRUNC | O_WRONLY;
	(*redir)->fdio = 1;
	if (((*redir)->fdarg = open((*redir)->arg->cmd[0], mode, 0644)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	next = (*redir)->next;
	if (!((*redir)->next = ft_memalloc(sizeof(*(*redir)->next))))
		return (redirect_error(ERR_MALLOC, (*redir)->arg->cmd[0], e));
	(*redir)->next->fdio = 2;
	(*redir)->next->fdarg = (*redir)->fdarg;
	(*redir)->next->next = next;
	*redir = (*redir)->next;
	return (0);
}

int				redirect_great_and(t_redirection **redir, t_s_env *e)
{
	size_t		i;
	int			mode;

	i = 0;
	mode = O_CREAT | O_TRUNC | O_WRONLY;
	(*redir)->fdio = ((*redir)->ionumber) ? ft_atoi((*redir)->ionumber->head) : 1;
	if (!ft_strcmp((*redir)->arg->cmd[0], "-"))
	{
		if (((*redir)->fdarg = open("/dev/null", O_RDWR)) < 0)
			return (redirect_open_error("/dev/null", e));
		return (0);
	}
	while ((*redir)->arg->cmd[0][i] && ft_isdigit((*redir)->arg->cmd[0][i]))
		i++;
	if (!(*redir)->arg->cmd[0][i])
		(*redir)->fdarg = ft_atoi((*redir)->arg->cmd[0]);
	else if ((*redir)->fdio != 1)
		return (redirect_error(ERR_AMBIGUOUS, (*redir)->arg->cmd[0], e));
	else if (((*redir)->fdarg = open((*redir)->arg->cmd[0], mode, 0644)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	if (fcntl((*redir)->fdarg, F_GETFD) < 0)
		return (redirect_error(ERR_BAD_FD, (*redir)->arg->cmd[0], e));
	return (0);
}

int				redirect_dgreat(t_redirection **redir, t_s_env *e)
{
	int			mode;

	mode = O_CREAT | O_APPEND | O_WRONLY;
	(*redir)->fdio = ((*redir)->ionumber) ? ft_atoi((*redir)->ionumber->head) : 1;
	if (((*redir)->fdarg = open((*redir)->arg->cmd[0], mode, 0644)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	return (0);
}

int				redirect_and_dgreat(t_redirection **redir, t_s_env *e)
{
	t_redirection	*next;
	int				mode;

	mode = O_CREAT | O_APPEND | O_WRONLY;
	(*redir)->fdio = 1;
	if (((*redir)->fdarg = open((*redir)->arg->cmd[0], mode, 0644)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	next = (*redir)->next;
	if (!((*redir)->next = ft_memalloc(sizeof(*(*redir)->next))))
		return (redirect_error(ERR_MALLOC, (*redir)->arg->cmd[0], e));
	(*redir)->next->fdio = 2;
	(*redir)->next->fdarg = (*redir)->fdarg;
	(*redir)->next->next = next;
	*redir = (*redir)->next;
	return (0);
}

int				redirect_dless(t_redirection **redir, t_s_env *e)
{
	ft_putendl("redirect_tless");
	(void)redir;
	(void)e;
	return (0);
}

int				redirection(t_redirection **redir, t_s_env *e)
{
	static int		(*handler[])(t_redirection **, t_s_env *) = {
		redirect_less, redirect_less_and, redirect_less_great, redirect_great,
		redirect_great_pipe, redirect_and_great, redirect_great_and,
		redirect_dgreat, redirect_and_dgreat, redirect_dless,
	};

	(*redir)->fdio = -1;
	(*redir)->fdarg = -1;
	return (handler[(*redir)->token->id - LESS_VALUE](redir, e));
}
