/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 00:59:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/24 07:31:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "operator_types.h"

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
