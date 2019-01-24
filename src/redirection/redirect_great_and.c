/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_great_and.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:25:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/24 07:39:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"

int				redirect_great_and(t_redirection **redir, t_s_env *e)
{
	size_t		i;
	int			mode;

	i = 0;
	mode = O_CREAT | O_TRUNC | O_WRONLY;
	(*redir)->fdio = 1;
	if ((*redir)->ionumber)
		(*redir)->fdio = ft_atoi((*redir)->ionumber->head);
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
