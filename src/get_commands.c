/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 02:03:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/18 20:32:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static t_cmd	*parse_line(const char *line)
{
	t_cmd		*cmd;

	cmd = (t_cmd *)0;
	if (!line || !*line)
		return (t_cmd *)(0);
	return (cmd);
}

void		get_commands(t_token *tokens)
{
	while (tokens)
	{
		tokens->head = parse_line(tokens->line);
		tokens = tokens->next;
	}
}