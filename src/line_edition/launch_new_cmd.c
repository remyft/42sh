/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_new_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 20:31:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 20:32:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "token.h"
#include "command.h"

static void		remove_line_continuation(char **line)
{
	size_t		i;

	i = 0;
	if (line && *line)
		while ((*line)[i])
		{
			if ((*line)[i] == '\\' && (*line)[i + 1] == '\n')
				ft_strcpy(&(*line)[i], &(*line)[i + 2]);
			else
				i++;
		}
}

void			launch_new_cmd(char **line, t_s_env *e)
{
	t_token		*tokens;
	t_m_list	*tree;

	tokens = NULLTOKEN;
	tree = NULLLIST;
	remove_line_continuation(line);
	if (!e->forked && !e->interactive)
		term_restore(&e->save);
	if ((tokens = tokenise(line, e)) != NULLTOKEN)
	{
		if ((tree = parse(line, &tokens, e)) != NULLLIST)
			execute_list(tree, e);
		free_m_list(&tree);
		free_token(&tokens);
	}
	if (!e->forked && !e->interactive)
		define_new_term(&e->save);
}
