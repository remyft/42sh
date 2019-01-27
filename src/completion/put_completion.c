/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:42:34 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/27 20:39:40 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "put.h"
#include "shell_lib.h"

static int	deal_select(t_slct *select, t_cpl_e env, t_line *line)
{
	int		tres;
	int		psb;

	psb = 0;
	tres = 0;
	get_psb(select, ft_strlen(env.chr), 0, &psb);
	if (psb == 1)
	{
		if (!ft_strcmp(env.chr, line->curr->buff_tmp))
			ret_psb(select, ft_strlen(env.chr), 0, line->curr->buff);
		else
			ret_psb(select, ft_strlen(env.chr), 0,
					!sh_strchr(ft_strrchr(line->curr->buff, ' '), '/')
					? sh_strrchr(line->curr->buff, ' ') + 1
					: sh_strrchr(line->curr->buff, '/') + 1);
		free(env.chr);
		free_select(select);
		return (1);
	}
	if (line->is_putb && line->key)
		deal_slct_key(select, env.nb_col, line->key);
	get_isput(select, ft_strlen(env.chr), 1, &tres);
	if (!tres)
		reset_isput(select, ft_strlen(env.chr), 1);
	return (0);
}

static int	deal_tree(t_line *line, t_tree *tern, t_cpl_e env)
{
	int		tres;
	int		psb;
	char	*tmp;
	char	*chr;

	tres = 0;
	psb = 0;
	get_tree_psb(tern, &psb);
	if (psb == 1)
	{
		if ((chr = sh_strrchr(line->curr->buff, ' ')))
			tmp = sh_strchr(chr, '/') ? sh_strrchr(chr, '/') : chr;
		if (tern->value != '.')
			get_tstr(tern, tmp);
		else
			tern->left ? get_tstr(tern->left, tmp) : get_tstr(tern->right, tmp);
		return (1);
	}
	if (line->is_putb && line->key)
		deal_tree_key(tern, env.nb_col, line->key);
	get_put(tern, &tres, *env.chr);
	if (!tres)
		reset_put(tern);
	return (0);
}

static void	init_cpl(t_cpl_e *env, t_line *line, int *put, int *nb_ret)
{
	env->put = put;
	env->nb_ret = nb_ret;
	env->nb_col = line->nb_col / (env->lenm + 1);
	env->len = ft_strlen(env->chr);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	put_prompt(line->prompt);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
}

static int	deal_put(t_line *line, t_cpl_e env, t_slct *select, t_tree *tern)
{
	if (select && deal_select(select, env, line))
		return (1);
	else if (!select && deal_tree(line, tern, env))
		return (1);
	if (select)
		put_select_branch(select, env, line);
	else if (env.lenm)
		put_tree_branch(tern, env, line);
	else
	{
		if (env.chr)
			free(env.chr);
		return (-1);
	}
	return (0);
}

int			put_complet(t_tree *tern, int *put, t_line *line, int *nb_ret)
{
	t_slct	*select;
	t_cpl_e	env;
	int		ret;

	env.chr = NULL;
	env.bru[0] = 0;
	select = NULL;
	if ((env.lenm = get_select(line, tern, &(env.chr), &select)) == -1)
		return (-1);
	init_cpl(&env, line, put, nb_ret);
	if ((ret = deal_put(line, env, select, tern)))
		return (ret);
	if (*line->e_cmpl & COMPLETION)
		if (line->is_putb < 2)
			line->is_putb += 1;
	*(line->e_cmpl) |= COMPLETION;
	if (env.chr)
		free(env.chr);
	if (select)
		free_select(select);
	return (0);
}
