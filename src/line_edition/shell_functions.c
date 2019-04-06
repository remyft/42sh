/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 20:10:26 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/06 16:17:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "history.h"
#include "command.h"
#include "main_tools.h"
#include "parser.h"
#include "token.h"
#include "libft.h"
#include "shell_term.h"

void			launch_new_cmd(char **line, t_s_env *e)
{
	t_token		*tokens;
	t_m_list	*tree;
	size_t		i;

	tokens = NULLTOKEN;
	tree = NULLLIST;
	i = 0;
	if (line && *line)
		while ((*line)[i])
		{
			if ((*line)[i] == '\\' && (*line)[i + 1] == '\n')
				ft_strcpy(&(*line)[i], &(*line)[i + 2]);
			else
				i++;
		}
	if ((tokens = tokenise(*line, e)) != NULLTOKEN)
	{
		if (!parse_quote(line, &tokens, e)
		&& (tree = parse(line, &tokens, e)) != NULLLIST)
			execute_list(tree, e);
		free_m_list(&tree);
		free_token(&tokens);
	}
}

static void		get_cursor_pos(void)
{
	static char	cmd[] = "\033[6n";
	char		buf[15];
	int			nb_read;
	char		*ptr;

	ft_memset(buf, 0, sizeof(buf));
	write(STDIN_FILENO, cmd, sizeof(cmd));
	if ((nb_read = read(STDIN_FILENO, buf, sizeof(buf) - 1)) < 0)
		return ;
	buf[nb_read] = 0;
	if (!(ptr = ft_strchr(buf, ';')))
		return ;
	ptr++;
	if (ft_atoi(ptr) == 1)
		return ;
	tputs(tgetstr("mr", NULL), 1, ft_pchar);
	tputs("%", 1, ft_pchar);
	tputs(tgetstr("me", NULL), 1, ft_pchar);
	tputs("\n", 1, ft_pchar);
}

static void		get_new_cmd(t_line *line, t_s_env *e)
{
	char		*ret;

	ret = ft_strdup(line->curr->buff);
	*(line->e_cmpl) &= ~COMPLETION;
	launch_new_cmd(&ret, e);
	get_cursor_pos();
	if (ret)
		save_history(line, ret, &(line->hist), e->public_env);
	ft_strdel(&ret);
	init_new_buff(line);
	del_all_state(line);
	reset_hist(line);
	GET_TREE(line->tree, FILES) = free_tree(line->tree[1]);
	GET_TREE(line->tree, FILES) = create_file_tree(".", NULL, line->tree[1]);
}

void			init_shell_line(t_line **line, t_s_env *e)
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

void			shell_loop(t_line *line, t_s_env *e)
{
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	while (e->shell_loop && line->shell_loop)
	{
		put_prompt(line->prompt);
		check_path(line, e->public_env);
		deal_typing(line);
		write(1, "\n", 1);
		if (line->curr->buff[0] && line->tmp[0] != -1
				&& line->curr->buff[0] != 10)
			get_new_cmd(line, e);
	}
}
