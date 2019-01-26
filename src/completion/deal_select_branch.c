/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_select_branch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:40:31 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 01:43:53 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "libft.h"

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

int			get_select(t_line *line, t_tree *tern, char **chr, t_slct **select)
{
	int		lenm;

	lenm = 0;
	if (!ft_strchr(line->curr->buff_tmp, ' '))
	{
		*chr = ft_strdup(line->curr->buff_tmp);
		if (!(*select = select_branch(tern, *chr, &lenm)))
		{
			free(*chr);
			return (-1);
		}
	}
	else if (*(*chr = !ft_strchr(ft_strrchr(line->curr->buff_tmp, ' '), '/')
				? ft_strdup(ft_strrchr(line->curr->buff_tmp, ' ') + 1)
				: ft_strdup(ft_strrchr(line->curr->buff_tmp, '/') + 1)))
	{
		if (!(*select = select_branch(tern, *chr, &lenm)))
		{
			free(*chr);
			return (-1);
		}
	}
	else
		get_max_len(tern, &lenm);
	return (lenm);
}
