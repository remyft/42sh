/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_great.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:27:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/05 19:51:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"

int				redirect_great(t_redirection **redir, t_s_env *e)
{
	int			mode;

	mode = O_CREAT | O_TRUNC | O_WRONLY;
	(*redir)->fdio = (*redir)->ionumber ? ft_atoi((*redir)->ionumber->head) : 1;
	if (((*redir)->fdarg = open((*redir)->arg->cmd[0], mode, 0644)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	return (0);
}
