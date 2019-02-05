/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_select_branch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:40:31 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/05 01:19:48 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "shell.h"
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

int			have_to_expand(t_line *line)
{
	char	*space;
	char	*slash;
	char	*dol;

	space = sh_strrchr(line->curr->buff, ' ');
	slash = sh_strrchr(line->curr->buff, '/');
	if (!(dol = sh_strrchr(line->curr->buff, '$')))
		return (0);
	if (!space && dol)
		return (1);
	if (space && !slash && dol > space)
		return (1);
	if (space && slash && dol > slash && dol > space)
		return (1);
	return (0);
}

int			get_select(t_line *line, t_tree *tern, t_cpl_e *env,
		t_slct **select)
{
	int		lenm;

	lenm = 0;
	if ((env->is_dol = have_to_expand(line)))
	{
		env->ptr = sh_strrchr(line->curr->buff_tmp, '$');
		if (!*(env->ptr + 1) || (*(env->ptr + 1) == '{' && !*(env->ptr + 2)))
		{
			env->chr = ft_strdup(line->curr->buff_tmp);
			get_max_len(tern, &lenm);
		}
		else
		{
			env->chr = *(env->ptr + 1) == '{' ? ft_strdup(env->ptr + 2)
				: ft_strdup(env->ptr + 1);
			if (!(*select = select_branch(tern, env->chr, &lenm)))
			{
				free(env->chr);
				return (-1);
			}
		}
	}
	else if (!(env->ptr = sh_strrchr(line->curr->buff_tmp, ' ')))
	{
		env->chr = ft_strdup(line->curr->buff_tmp);
		if (!(*select = select_branch(tern, env->chr, &lenm)))
		{
			free(env->chr);
			return (-1);
		}
	}
	else if (*(env->chr = !sh_strchr(env->ptr, '/') ? ft_strdup(env->ptr + 1)
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
