/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:42:34 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/24 09:50:58 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "put.h"

typedef struct	s_cpl_env
{
	int		len;
	int		lenm;
	int		nb_col;
	int		*put;
	int		*nb_ret;
	int		lvl;
	char	bru[257];
}				t_cpl_e;

void	get_new_file(t_tree *tern, t_cpl_e env, t_line *line)
{
	char	*chr;
	int		i;
	if (!*(ft_strrchr(line->curr->buff, ' ') + 1))
		stercat(line->curr->buff_tmp, env.bru, line->curr->buff);
	else if (!ft_occuc(ft_strrchr(line->curr->buff, ' '), '/'))
	{
		chr = ft_strrchr(line->curr->buff, ' ') + 1;
		i = 0;
		while (&(line->curr->buff)[i] != chr)
			i++;
		ft_strcpy(&(line->curr->buff)[i], env.bru);
	}
	else
	{
		chr = ft_strrchr(line->curr->buff, '/') + 1;
		i = 0;
		while (&(line->curr->buff)[i] != chr)
			i++;
		ft_strcpy(&(line->curr->buff)[i], env.bru);
	}
	ft_strncat(line->curr->buff, (char*)&(tern->value), 1);
}

void	get_new_buff(t_tree *tern, t_cpl_e env, t_line *line)
{
	if (!tern->tput && *env.put && *(line->e_cmpl) & COMPLETION)
	{
		tputs(tgetstr("mr", NULL), 1, ft_pchar);
		tern->tput = 1;
		*env.put = 0;
		if (ft_occuc(line->curr->buff, ' '))
			get_new_file(tern, env, line);
		else
		{
			ft_bzero(line->curr->buff, ft_strlen(line->curr->buff));
			ft_strcpy(line->curr->buff, env.bru);
			ft_strncat(line->curr->buff, (char *)&(tern->value), 1);
		}
	}
	else
		tputs(tgetstr("me", NULL), 1, ft_pchar);
}

void	put_space(t_cpl_e env, int *car_ret)
{
	if (*car_ret < env.nb_col - 1)
	{
		ft_putchars(' ', env.lenm - ft_strlen(env.bru) + 1);
		*car_ret += 1;
	}
	else
	{
		ft_putchars(' ', env.lenm - ft_strlen(env.bru) + 1);
		ft_putchar('\n');
		*car_ret = 0;
		*env.nb_ret += 1;
	}
}

void	ft_put_tree(t_tree *tern, t_cpl_e env, t_line *line, int *car_ret)
{
	if (tern->left)
		ft_put_tree(tern->left, env, line, car_ret);
	if (tern->tern_next && (tern->value != '.' || env.bru[0] == '.' || env.lvl >= 1))
	{
		env.bru[env.lvl] = tern->value;
		env.lvl += 1;
		ft_put_tree(tern->tern_next, env, line, car_ret);
		env.lvl -= 1;
	}
	if (tern && !tern->tern_next)
	{
		env.bru[env.lvl] = '\0';
		get_new_buff(tern, env, line);
		ft_putstr(env.bru);
		put_space(env, car_ret);
	}
	if (tern->right)
		ft_put_tree(tern->right, env, line, car_ret);
}

t_slct		*select_branch(t_tree *upper, char *src, int *lenm);

int		free_null(void *data)
{
	free(data);
	return (0);
}

int		deal_upper(t_tree *upper, char *src, int *lenm, t_slct **select)
{
	if (!upper)
		return (1);
	while (upper->value != ft_toupper(*src))
		if (!(upper = ft_toupper(*src) < upper->value ? upper->left : upper->right))
			return (1);
	if (!(src[1]))
		*lenm = upper->max_len > *lenm ? upper->max_len : *lenm;
	*select = ft_memalloc(sizeof(t_slct));
	(*select)->mln = upper;
	if (*(src + 1) && !((*select)->down = select_branch(upper->tern_next, src + 1, lenm)))
		return (free_null(*select));
	return (1);
}

int		deal_lower(t_tree *lower, char *src, int *lenm, t_slct **select)
{
	while (lower && lower->value != ft_tolower(*src))
		lower = ft_tolower(*src) < lower->value ? lower->left : lower->right;
	if (lower && !(src[1]))
		*lenm = lower->max_len > *lenm ? lower->max_len : *lenm;
	if (lower)
	{
		if (*select)
		{
			(*select)->next = ft_memalloc(sizeof(t_slct));
			(*select)->next->prev = *select;
			(*select)->next->mln = lower;
			if (*(src + 1) && !((*select)->next->down
						= select_branch(lower->tern_next, src + 1, lenm)))
				return (free_null(*select));
		}
		else
		{
			*select = ft_memalloc(sizeof(t_slct));
			(*select)->mln = lower;
			if (*(src + 1) && !((*select)->down) && !((*select)->down
						= select_branch(lower->tern_next, src + 1, lenm)))
				return (free_null(*select));
		}
	}
	return (1);
}

t_slct		*select_branch(t_tree *upper, char *src, int *lenm)
{
	t_slct	*select;
	t_tree	*lower;

	select = NULL;
	lower = upper;
	if (*src)
		if (!(deal_upper(upper, src, lenm, &select)))
			return (NULL);
	if (*src && ft_toupper(*src) != ft_tolower(*src))
			if (!(deal_lower(lower, src, lenm, &select)))
				return (NULL);
	return (select);
}

void	put_branch(t_slct *select, t_cpl_e env, t_line *line, int *car_ret)
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

void	put_select_branch(t_slct *select, t_cpl_e env, t_line *line)
{
	int		car_ret;

	car_ret = 0;
	env.lvl = 0;
	put_branch(select, env, line, &car_ret);
}

void	put_tree_branch(t_tree *tree, t_cpl_e env, t_line *line)
{
	int		car_ret;

	car_ret = 0;
	env.lvl = 0;
	ft_put_tree(tree, env, line, &car_ret);
}

void	count_elem(t_tree *tree, int *cpt)
{
	if (tree->left)
		count_elem(tree->left, cpt);
	if (tree->tern_next && (tree->prev || tree->value != '.'))
		count_elem(tree->tern_next, cpt);
	else if (!tree->tern_next)
	{
		if (tree->tput)
			*cpt += 1;
	}
	if (tree->right)
		count_elem(tree->right, cpt);
}

void	change_elem(t_tree *tree, int val, int *cpt)
{
	if (tree->left)
		change_elem(tree->left, val, cpt);
	if (tree->tern_next && (tree->prev || tree->value != '.'))
		change_elem(tree->tern_next, val, cpt);
	else if (!tree->tern_next)
	{
		if (*cpt == val - 1)
			tree->tput = 0;
		else
		{
			tree->tput = 1;
			*cpt += 1;
		}
	}
	if (tree->right)
		change_elem(tree->right, val, cpt);
}

void	deal_slct_key_left(t_tree *select, t_tree *tree, int nb_elem)
{
	int		cpt;
	int		flg;

	cpt = 0;
	flg = 0;
	count_elem(select, &cpt);
	if (tree)
		count_elem(tree, &cpt);
	if (cpt == 1 || cpt == 0)
		cpt = nb_elem + 1;
	change_elem(select, cpt - 1, &flg);
	if (tree)
		change_elem(tree, cpt - 1, &flg);
}

void	deal_slct_key_up(t_tree *select, t_tree *tree, int nb_elem, int nb_col)
{
	int		cpt;
	int		flg;
	int		tmp;

	cpt = 0;
	flg = 0;
	count_elem(select, &cpt);
	if (tree)
		count_elem(tree, &cpt);
	if (cpt - nb_col <= 0)
	{
		tmp = cpt % nb_col;
		cpt = nb_elem;
		while (cpt % nb_col != tmp)
			cpt--;
		cpt += nb_col;
	}
	change_elem(select, cpt - nb_col, &flg);
	if (tree)
		change_elem(tree, cpt - nb_col, &flg);

}

void	deal_slct_key_down(t_tree *select, t_tree *tree, int nb_elem, int nb_col)
{
	int		cpt;
	int		flg;

	cpt = 0;
	flg = 0;
	count_elem(select, &cpt);
	if (tree)
		count_elem(tree, &cpt);
	if (cpt + nb_col > nb_elem)
	{
		if (cpt % nb_col == 0)
			cpt = 0;
		else
			cpt = cpt % nb_col - nb_col;
	}
	change_elem(select, cpt + nb_col, &flg);
	if (tree)
		change_elem(tree, cpt + nb_col, &flg);
}

void	deal_slct_winch(t_tree *select, t_tree *tree)
{
	int		cpt;
	int		flg;

	cpt = 0;
	flg = 0;
	count_elem(select, &cpt);
	if (tree)
		count_elem(tree, &cpt);
	reset_put(select);
	if (tree)
		reset_put(tree);
	change_elem(select, cpt, &flg);
	if (tree)
		change_elem(tree, cpt, &flg);

}

void	deal_slct_key(t_slct *select, int nb_col, int key)
{
	int		tmp;
	t_tree	*tree;

	tree = NULL;
	if (select->down)
		deal_slct_key(select->down, nb_col, key);
	else
	{
		if (select->next)
			tree = select->next->mln->tern_next;
		tmp = select->mln->tern_next->npsb;
		if (select->next)
			tmp += select->next->mln->tern_next->npsb;
		if (key == DOWN)
			deal_slct_key_down(select->mln->tern_next, tree, tmp, nb_col);
		else if (key == UP)
			deal_slct_key_up(select->mln->tern_next, tree, tmp, nb_col);
		else if (key == LEFT)
			deal_slct_key_left(select->mln->tern_next, tree, tmp);
		else if (key == WINCH)
			deal_slct_winch(select->mln->tern_next, tree);
		return ;
	}
	if (select->next)
		deal_slct_key(select->next, nb_col, key);
}

void	get_tree_psb(t_tree *tree, int *psb)
{
	if (tree->left)
		get_tree_psb(tree->left, psb);
	if (tree->right)
		get_tree_psb(tree->right, psb);
	if ((tree->prev || tree->value != '.') && tree->tern_next)
		get_tree_psb(tree->tern_next, psb);
	if (!tree->tern_next)
		*psb += 1;
}


void	deal_tree_key(t_tree *tree, int nb_col, int key)
{
	int		psb;

	psb = 0;
	get_tree_psb(tree, &psb);
	if (key == DOWN)
		deal_slct_key_down(tree, NULL, psb, nb_col);
	else if (key == UP)
		deal_slct_key_up(tree, NULL, psb, nb_col);
	else if (key == LEFT)
		deal_slct_key_left(tree, NULL, psb);
	else if (key == WINCH)
		deal_slct_winch(tree, NULL);
}

void	free_select(t_slct *select)
{
	if (select->next)
		free_select(select->next);
	if (select->down)
		free_select(select->down);
	if (select)
		free(select);
}

int		get_select(t_line *line, t_tree *tern, char **chr, t_slct **select)
{
	int		lenm;

	lenm = 0;
	if (!ft_strchr(line->curr->buff_tmp, ' '))
	{
		*select = select_branch(tern, (*chr = ft_strdup(line->curr->buff_tmp)), &lenm);
		if (!*select)
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

#include <stdio.h>

int		deal_select(t_slct *select, char *chr, t_line *line, int nb_col)
{
	int		tres;
	int		psb;

	psb = 0;
	get_psb(select, ft_strlen(chr), 0, &psb);
	if (psb == 1)
	{
		if (!ft_strcmp(chr, line->curr->buff_tmp))
			ret_psb(select, ft_strlen(chr), 0, line->curr->buff);
		else
			ret_psb(select, ft_strlen(chr), 0,
					!ft_strchr(ft_strrchr(line->curr->buff, ' '), '/')
					? ft_strrchr(line->curr->buff, ' ') + 1
					: ft_strrchr(line->curr->buff, '/') + 1);
		free(chr);
		return (1);
	}
	if (line->is_putb && line->key)
		deal_slct_key(select, nb_col, line->key);
	get_isput(select, ft_strlen(chr), 1, &tres);
	if (!tres)
		reset_isput(select, ft_strlen(chr), 1);
	return (0);
}

void	deal_tree(t_line *line, t_tree *tern, int nb_col, char *chr)
{
	int		tres;

	tres = 0;
	if (line->is_putb && line->key)
		deal_tree_key(tern, nb_col, line->key);
	get_put(tern, &tres, *chr);
	if (!tres)
		reset_put(tern);
}

int		put_complet(t_tree *tern, int *put, t_line *line, int *nb_ret)
{
	t_slct	*select;
	t_cpl_e	env;
	char	*chr;

	env.lenm = 0;
	env.put = put;
	env.nb_ret = nb_ret;
	chr = NULL;
	select = NULL;
	if ((env.lenm = get_select(line, tern, &chr, &select)) == -1)
		return (-1);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	put_prompt(line->prompt);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	env.nb_col = line->nb_col / (env.lenm + 1);
	if (select && deal_select(select, chr, line, env.nb_col))
		return (1);
	else if (!select)
		deal_tree(line, tern, env.nb_col, chr);
	env.len = ft_strlen(chr);
	if (select)
		put_select_branch(select, env, line);
	else if (env.lenm)
		put_tree_branch(tern, env, line);
	else
	{
		if (chr)
			free(chr);
		return (-1);
	}
	if (*line->e_cmpl & COMPLETION)
		line->is_putb = 1;
	*(line->e_cmpl) |= COMPLETION;
	if (chr)
		free(chr);
	if (select)
		free_select(select);
	return (0);
}

