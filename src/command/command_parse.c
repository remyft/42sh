/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/02/28 13:47:46 by dbaffier         ###   ########.fr       */
=======
/*   Updated: 2019/03/01 12:53:32 by gbourgeo         ###   ########.fr       */
>>>>>>> 827b690da80e545cc6fef32a20c656727c1d60ae
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"

int				command_parse(void *cmd, t_s_env *e)
{
	t_execute	exec;

	if (*(int *)cmd == IS_A_PIPE)
		return (command_pipe(cmd, e, (int [2]){ 0, 0 }));
	command_debug(cmd);
	ft_memset(&exec, 0, sizeof(exec));
	if (!((t_command *)cmd)->args)
		return (0);
	exec.variable = ((t_command *)cmd)->args;
	exec.redirection = ((t_command *)cmd)->redir;
	return (command_prepare(&exec, e));
}
