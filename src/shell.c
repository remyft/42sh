/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:46:11 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/19 09:28:38 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "history.h"
#include "main_tools.h"
#include "parser.h"
#include "shell.h"
#include "shell_env.h"
#include "shell_term.h"
#include "token.h"
#include "job_control.h"

void			launch_new_cmd(char **line, t_s_env *e)
{
	t_token		*tokens;
	t_m_list	*tree;

	tokens = NULLTOKEN;
	tree = NULLLIST;
	if ((tokens = tokenise(*line, e)) != NULLTOKEN)
	{
		if ((tree = parse(line, &tokens, e)) != NULLLIST)
		{
			term_restore(e->save);
			execute_list(tree, e);
			define_new_term(&e->save);
			free_m_list(&tree);
		}
		free_token(&tokens);
	}
}

static void		get_new_cmd(t_line *line, t_s_env *e)
{
	char		*ret;

	ret = listnjoin(line);
	*(line->e_cmpl) &= ~COMPLETION;
	launch_new_cmd(&ret, e);
	if (ret)
		save_history(line, ret, &(line->hist), e->public_env);
	ft_strdel(&ret);
	init_new_buff(line);
	del_all_state(line);
	reset_hist(line);
	GET_TREE(line->tree, FILES) = free_tree(line->tree[1]);
	GET_TREE(line->tree, FILES) = create_file_tree(".", NULL, line->tree[1]);
}

static void		init_shell_line(t_line **line, t_s_env *e)
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

#include <stdio.h>

static void		shell_loop(t_line *line, t_s_env *e)
{
	while (e->shell_loop && line->shell_loop)
	{
		jobs_notify_ended(e->jobs);
		jobs_remove(&e->jobs, 1);
		put_prompt(line->prompt);
		check_path(line, e->public_env);
		deal_typing(line);
		if (line->curr->buff[0] && line->tmp[0] != -1
				&& line->curr->buff[0] != 10)
		{
			get_new_cmd(line, e);
		}
	}
}

int				main(int ac, char **av, char **ep)
{
	t_line		*line;
	t_s_env		e;

	line = NULL;
	init_shell_env(&e, ac, av, ep);
	init_shell_line(&line, &e);
	define_new_term(&e.save);
	get_rc(&e);
	shell_loop(line, &e);
	term_restore(e.save);
	free_shell_env(&e);
	free_struct(line);
	return (e.ret);
}
