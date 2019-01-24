/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_less_and.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:28:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/24 07:39:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"

int				redirect_less_and(t_redirection **redir, t_s_env *e)
{
	size_t		i;

	i = 0;
	(*redir)->fdio = 0;
	if ((*redir)->ionumber)
		(*redir)->fdio = ft_atoi((*redir)->ionumber->head);
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
