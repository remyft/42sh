/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:46:11 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/27 13:52:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "main_tools.h"
#include "token.h"
#include "parser.h"
#include "execution.h"
#include "shell_env.h"

static void	get_new_cmd(t_line *line, t_s_env *e)
{
	char		*ret;
	t_token		*tokens;
	t_m_list	*tree;

	tokens = NULLTOKEN;
	tree = NULLLIST;
	ret = listnjoin(line);
	*(line->e_cmpl) &= ~COMPLETION;
	save_history(line->index, ret, &(line->hist), e->public_env);
	ret = ft_strjoinfree(ret, "\n", 1);
	remove_line_continuation(ret);
	if ((tokens = tokenise(ret)) != NULLTOKEN)
	{
		if ((tree = parse(tokens)) != NULLLIST)
		{
			execute_list(tree, e);
			free_m_list(&tree);
		}
		free_token(&tokens);
	}
	free_buff(line);
	del_all_state(line);
	line->tree[1] = free_tree(line->tree[1]);
	line->tree[1] = create_file_tree(".", line->tree[1]);
	free(ret);
}

static void	init_shell_line(t_line **line, t_s_env *e)
{
	*line = get_struct();
	init_line(e->public_env, *line);
	(*line)->curr = ft_memalloc(sizeof(t_buff));
	(*line)->beg_buff = (*line)->curr;
}

static void	shell_loop(t_line *line, t_s_env *e)
{
	while (1)
	{
		put_prompt(line->prompt);
		check_path(line, e->public_env);
		deal_typing(line);
		if (!deal_hdoc(line))
			if (check_hdoc(line))
				continue ;
		if (line->curr->buff[0] && line->tmp[0] != -1
				&& line->curr->buff[0] != 10)
			get_new_cmd(line, e);
	}
}

int			main(int ac, char **av, char **ep)
{
	t_line		*line;
	t_s_env		e;

	line = NULL;
	init_shell_env(&e, ac, av, ep);
	init_shell_line(&line, &e);
	define_new_term(&e.save);
	shell_loop(line, &e);
	free_shell_env(&e);
	return (0);
}
