/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_group.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:29:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/15 03:49:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static char		**alloc_command(t_argument *cmd)
{
	char		**ret;
	size_t		size;
	size_t		i;

	size = 0;
	while (cmd)
	{
		i = 0;
		if (cmd->cmd)
			while (cmd->cmd[i])
				i++;
		size += i;
		cmd = cmd->next;
	}
	return (ft_memalloc(sizeof(*ret) * (size + 1)));
}

char			**command_group(t_argument *cmd)
{
	char		**ret;
	size_t		i;
	size_t		j;

	if (!(ret = alloc_command(cmd)))
		return (NULL);
	i = 0;
	while (cmd)
	{
		j = 0;
		if (cmd->cmd)
			while (cmd->cmd[j])
				ret[i++] = cmd->cmd[j++];
		cmd = cmd->next;
	}
	return (ret);
}
