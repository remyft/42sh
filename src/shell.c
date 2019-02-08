/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:46:11 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/07 06:32:49 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "main_tools.h"
#include "token.h"
#include "parser.h"
#include "command.h"
#include "shell_env.h"
#include "history.h"
#include "shell_term.h"

void		launch_new_cmd(char **line, t_s_env *e)
{
	t_token		*tokens;
	t_m_list	*tree;

	tokens = NULLTOKEN;
	tree = NULLLIST;
	*line = ft_strjoinfree(*line, "\n", 1);
	remove_line_continuation(*line);
	if ((tokens = tokenise(*line)) != NULLTOKEN)
	{
		if ((tree = parse(tokens)) != NULLLIST)
		{
			execute_list(tree, e);
			free_m_list(&tree);
		}
		free_token(&tokens);
	}
}

static void	get_new_cmd(t_line *line, t_s_env *e)
{
	char		*ret;

	ret = listnjoin(line);
	save_history(line, ret, &(line->hist), e->public_env);
	launch_new_cmd(&ret, e);
	free(ret);
	init_new_buff(line);
	del_all_state(line);
	reset_hist(line);
	GET_TREE(line->tree, FILES) = free_tree(line->tree[1]);
	GET_TREE(line->tree, FILES) = create_file_tree(".", line->tree[1]);
}

static void	init_shell_line(t_line **line, t_s_env *e)
{
	if (!(*line = get_struct()))
	{
		free_shell_env(e);
		exit(1);
	}
	(*line)->public_env = &e->public_env;
	(*line)->private_env = &e->private_env;
	if (!((*line)->curr = ft_memalloc(sizeof(t_buff))))
	{
		free(line);
		free_shell_env(e);
		exit(1);
	}
	init_line(e->public_env, *line);
	(*line)->beg_buff = (*line)->curr;
}

static void	shell_loop(t_line *line, t_s_env *e)
{
	while (e->shell_loop && line->shell_loop)
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
	term_restore(e.save);
	free_shell_env(&e);
	free_struct(line);
	return (e.ret);
}
