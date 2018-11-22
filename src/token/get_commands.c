/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 02:03:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/22 05:21:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

// static int		ft_isspace(char c)
// {
// 	return ((c >= 9 && c <= 13) || c == ' ');
// }

// static t_cmd	*new_command(void)
// {
// 	t_cmd		*ret;

// 	ret = (t_cmd *)malloc(sizeof(*ret));
// 	if (!ret)
// 		return (t_cmd *)(0);
// 	ft_memset(ret, 0, sizeof(*ret));
// 	return (ret);
// }

// static t_cmd	*parse_line(const char *line, unsigned int i, unsigned int j)
// {
// 	t_cmd		*cmd;

// 	cmd = (t_cmd *)new_command();
// 	// if (!line || !*line)
// 	// 	return (t_cmd *)(0);
// 	while (line[i])
// 	{
// 		while (ft_isspace(line[i]))
// 			i++;
// 		j = i;
// 		if (line[i] == '\'')
// 		{
// 			cmd->type |= QUOTED;
// 			j = ++i;
// 			while (line[i] != '\'')
// 				i++;
// 			cmd->cmd = ft_strsub(line, j, i - j);
// 			//
// 		}
// 		else if (line[i] == '"')
// 		{
// 			cmd->type |= DQUOTED;
// 			j = ++i;
// 			while (line[i] != '"')
// 				i++;
// 			cmd->cmd = ft_strsub(line, j, i - j);
// 			//
// 		}
// 		else if (ft_isdigit(line[i]))
// 			;
// 		i++;
// 	}
// 	return (cmd);
// }

void		get_commands(t_token *tokens)
{
	while (tokens)
	{
		// tokens->head = parse_line(tokens->line, 0, 0);
		tokens = tokens->next;
	}
}