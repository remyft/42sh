/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_select_branch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:40:31 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/28 20:03:51 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "21sh.h"
#include "libft.h"
#include "shell_lib.h"

void		put_branch(t_slct *select, t_cpl_e env, t_line *line, int *car_ret)
{
	if (select && env.len > env.lvl + 1)
	{
		env.bru[env.lvl] = select->mln->value;
		env.lvl += 1;
		put_branch(select->down, env, line, car_ret);
		env.lvl -= 1;
	}
	else if (select)
	{
		env.bru[env.lvl] = select->mln->value;
		env.bru[env.lvl + 1] = '\0';
		env.lvl += 1;
		ft_put_tree(select->mln->tern_next, env, line, car_ret);
		env.lvl -= 1;
	}
	if (select && select->next)
		put_branch(select->next, env, line, car_ret);
}

void		put_select_branch(t_slct *select, t_cpl_e env, t_line *line)
{
	int		car_ret;

	car_ret = 0;
	env.lvl = 0;
	put_branch(select, env, line, &car_ret);
}

void		put_tree_branch(t_tree *tree, t_cpl_e env, t_line *line)
{
	int		car_ret;

	car_ret = 0;
	env.lvl = 0;
	ft_put_tree(tree, env, line, &car_ret);
}

void		free_select(t_slct *select)
{
	if (select->next)
		free_select(select->next);
	if (select->down)
		free_select(select->down);
	if (select)
		free(select);
}

#include <stdio.h>

void		get_ptr_tree(t_tree *tree, char **ptr)
{
	if (!tree)
		return ;
	if (tree->value == '.')
		if (!tree->left || !tree->right)
			tree->left ? get_ptr_tree(tree->left, ptr) : get_ptr_tree(tree->right, ptr);
	if (tree->left && tree->left->value != '.')
		return ;
	if (tree->right && tree->right->value != '.')
		return ;
	if (tree->value == '.')
		 return ;
	**ptr = tree->value;
	*ptr += 1;
	if (tree->tern_next)
		get_ptr_tree(tree->tern_next, ptr);
}

void		find_last_slct(t_slct *select, char **ptr)
{
	if (select->down)
		find_last_slct(select->down, ptr);
	else
		get_ptr_tree(select->mln->tern_next, ptr);
}

void		get_nb_slct(t_slct *select, int *nb)
{
	if (select->next)
	{
		*nb += 1;
		get_nb_slct(select->next, nb);
	}
	if (select->down)
		get_nb_slct(select->down, nb);
}

void		change_ptr(t_slct *select, char **ptr)
{
	**ptr = select->mln->value;
	*ptr += 1;
	if (select->down)
		change_ptr(select->down, ptr);
}

void		change_buff(t_slct *select, t_cpl_e *env, t_line *line, t_tree *tern)
{
	int		tmp;

	tmp = 1;
	if (!(env->ptr = ft_strrchr(line->curr->buff, '/')))
		if (!(env->ptr = ft_strrchr(line->curr->buff, ' ')))
			env->ptr = line->curr->buff + 1;
	env->ptr += 1;
	if (select)
	{
		get_nb_slct(select, &tmp);
		if (tmp == 1)
		{
			change_ptr(select, &env->ptr);
			find_last_slct(select, &env->ptr);
		}
	}
	else if (tern)
	{
		tmp = 0;
		get_tree_psb(tern, &tmp);
		if (tmp == 1)
			return ;
		get_ptr_tree(tern, &env->ptr);
	}
	go_home(line);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	put_prompt(line->prompt);
	ft_putstr(line->curr->buff);
}

int			get_select(t_line *line, t_tree *tern, t_cpl_e *env, t_slct **select)
{
	int		lenm;

	lenm = 0;
	if (!(env->ptr = sh_strrchr(line->curr->buff_tmp, ' ')))
	{
		env->chr = ft_strdup(line->curr->buff_tmp);
		if (!(*select = select_branch(tern, env->chr, &lenm)))
		{
			free(env->chr);
			return (-1);
		}
	}
	else if (*(env->chr = !ft_strchr(env->ptr, '/') ? ft_strdup(env->ptr + 1)
				: ft_strdup(sh_strrchr(line->curr->buff_tmp, '/') + 1)))
	{
		if (!(*select = select_branch(tern, env->chr, &lenm)))
		{
			free(env->chr);
			return (-1);
		}
	}
	else
		get_max_len(tern, &lenm);
	change_buff(*select, env, line, tern);
	return (lenm);
}
