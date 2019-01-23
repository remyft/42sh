/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:42:34 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/23 08:39:15 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "put.h"

void	ft_put_tree(t_tree *tern, char *bru, int lvl, int *car_ret, int nb_col,
		int len_max, int *put, char *tget, char *old, t_line *line, int *nb_ret)
{
	char	*chr;
	int		i;

	if (tern->left)
		ft_put_tree(tern->left, bru, lvl, car_ret, nb_col, len_max, put, tget, old, line, nb_ret);
	if (tern->tern_next && (tern->value != '.' || bru[0] == '.' || lvl >= 1))
	{
		bru[lvl] = tern->value;
		ft_put_tree(tern->tern_next, bru, lvl + 1, car_ret, nb_col, len_max, put, tget, old, line, nb_ret);
	}
	if (tern && !tern->tern_next)
	{
		bru[lvl] = '\0';
		if (!tern->tput && *put && *(line->e_cmpl) & COMPLETION)
		{
			tputs(tgetstr("mr", NULL), 1, ft_pchar);
			tern->tput = 1;
			*put = 0;
			if (tget)
			{
				if (ft_occuc(tget, ' '))
				{
					if (!*(ft_strrchr(tget, ' ') + 1))
						stercat(old, bru, tget);
					else if (!ft_occuc(ft_strrchr(tget, ' '), '/'))
					{
						chr = ft_strrchr(tget, ' ') + 1;
						i = 0;
						while (&tget[i] != chr)
							i++;
						ft_strcpy(&tget[i], bru);
					}
					else
					{
						chr = ft_strrchr(tget, '/') + 1;
						i = 0;
						while (&tget[i] != chr)
							i++;
						ft_strcpy(&tget[i], bru);
					}
					ft_strncat(tget, (char*)&(tern->value), 1);
				}
				else
				{
					ft_bzero(tget, ft_strlen(tget));
					ft_strcpy(tget, bru);
					ft_strncat(tget, (char *)&(tern->value), 1);
				}
			}
		}
		else
			tputs(tgetstr("me", NULL), 1, ft_pchar);
		ft_putstr(bru);
		//		ft_putchar(tern->value);
		if (*car_ret < nb_col - 1)
		{
			ft_putchars(' ', len_max - ft_strlen(bru) + 1);
			*car_ret += 1;
		}
		else
		{
			ft_putchars(' ', len_max - ft_strlen(bru) + 1);
			ft_putchar('\n');
			*car_ret = 0;
			*nb_ret += 1;
		}
	}
	if (tern->right)
		ft_put_tree(tern->right, bru, lvl, car_ret, nb_col, len_max, put, tget, old, line, nb_ret);
}

t_slct		*select_branch(t_tree *upper, char *src, int *lenm)
{
	t_slct	*select;
	t_tree	*lower;

	select = NULL;
	lower = upper;
	if (*src)
	{
		while (upper && upper->value != ft_toupper(*src))
			upper = ft_toupper(*src) < upper->value ? upper->left : upper->right;
		if (upper && !(src[1]))
			*lenm = upper->max_len > *lenm ? upper->max_len : *lenm;
		if (upper)
		{
			select = ft_memalloc(sizeof(t_slct));
			select->mln = upper;
			if (*(src + 1) && !(select->down = select_branch(upper->tern_next, src + 1, lenm)))
			{
				free(select);
				return (NULL);
			}
		}
	}
	if (*src && ft_toupper(*src) != ft_tolower(*src))
	{
		while (lower && lower->value != ft_tolower(*src))
			lower = ft_tolower(*src) < lower->value ? lower->left : lower->right;
		if (lower && !(src[1]))
			*lenm = lower->max_len > *lenm ? lower->max_len : *lenm;
		if (lower)
		{
			if (select)
			{
				select->next = ft_memalloc(sizeof(t_slct));
				select->next->prev = select;
				select->next->mln = lower;
				if (*(src + 1) && !(select->next->down = select_branch(lower->tern_next, src + 1, lenm)))
				{
					free(select);
					return (NULL);
				}
			}
			else
			{
				select = ft_memalloc(sizeof(t_slct));
				select->mln = lower;
				if (*(src + 1) && !(select->down) && !(select->down = select_branch(lower->tern_next, src + 1, lenm)))
				{
					free(select);
					return (NULL);
				}
			}
		}
	}
	return (select);
}

void	put_branch(t_slct *select, t_tree *tern, int len, char *bru, int lvl, int lenm, int *car_ret, int nb_col, int *put, char *tget, char *old, t_line *line, int *nb_ret)
{
	if (tern)
		return (ft_put_tree(tern, bru, lvl, car_ret, nb_col, lenm, put, tget, old, line, nb_ret));
	if (select && len > lvl + 1)
	{
		bru[lvl] = select->mln->value;
		put_branch(select->down, tern,  len, bru, lvl + 1, lenm, car_ret, nb_col, put, tget, old, line, nb_ret);
	}
	else if (select)
	{
		bru[lvl] = select->mln->value;
		bru[lvl + 1] = '\0';
		ft_put_tree(select->mln->tern_next, bru, lvl + 1, car_ret, nb_col, lenm, put, tget, old, line, nb_ret);
	}
	if (select && select->next)
		put_branch(select->next, tern, len, bru, lvl, lenm, car_ret, nb_col, put, tget, old, line, nb_ret);
}
#include <stdio.h>
int i = 0;
void	deal_comp_key(t_tree *tern, int val, int *cpt)
{
	t_tree *tmp;

	if (tern && tern->left)
		deal_comp_key(tern->left, val, cpt);
	if (tern && tern->tern_next)
		deal_comp_key(tern->tern_next, val, cpt);
	if (tern && !tern->tern_next)
		if (!tern->tput && *cpt < val)
		{
			i++;
			tern->tput = 1;
			tmp = tern;
		/*			while (tmp)
					{
					ft_putchar(tmp->value);
					tmp = tmp->prev;
					}
					ft_putendl("");*/
			*cpt += 1;
		}
	if (tern && tern->right)
		deal_comp_key(tern->right, val, cpt);
}

int		set_last_tree(t_tree *tern)
{
	if (tern->left)
		if (set_last_tree(tern->left))
			return (1);
	if (tern->tern_next)
		if (set_last_tree(tern->tern_next))
			return (1);
	if (!tern->tern_next)
	{
		tern->tput = 1;
		return (1);
	}
	if (tern->right)
		if (set_last_tree(tern->right))
			return (1);
	return (0);
}

void	deal_slct_key_up(t_slct *select, int val, int *cpt, int nb_col)
{
	int		tres;
	int		tmp;

	tres = 0;
	tmp = 0;
	deal_comp_key(select->mln->tern_next, val, cpt);
	if (val != *cpt)
	{
		if (select->next)
			get_put(select->next->mln->tern_next, &tres, select->next->mln->value);
		if (select->prev)
			get_put(select->prev->mln->tern_next, &tres, select->prev->mln->value);
		get_put(select->mln->tern_next, &tres, select->mln->value);
		if (!tres)
			reset_put(select->mln->tern_next);
		tmp = select->mln->tern_next->npsb;
		if (select->next)
			tmp += select->next->mln->tern_next->npsb;
		else if (select->prev)
			tmp += select->prev->mln->tern_next->npsb;
		if (tmp % (nb_col) != 0)
		{
		//	ft_putendl("YO");
		//	sleep(1);
	//		printf("cpt : %d, val : %d\n", *cpt, val);
			*cpt += nb_col - (tmp % (nb_col) - 1);
	//		printf("cpt : %d, val : %d\n", *cpt, val);
	//		ft_putendl("");
	//		sleep(1);
		}
		deal_comp_key(select->mln->tern_next, val, cpt);
	}
	if (val == *cpt)
	{
		*cpt = 0;
		get_put(select->mln->tern_next, &tres, select->mln->value);
		if (!tres)
		{
			reset_put(select->mln->tern_next);
	//		set_last_tree(select->mln->tern_next);
		}
	}

}

void	deal_slct_key_down(t_slct *select, int val, int *cpt, int nb_col)
{
	int		tres;
	int		tmp;

	tres = 0;
	tmp = 0;
	deal_comp_key(select->mln->tern_next, val, cpt);
	if (val != *cpt && !select->next)
	{
	//	if (select->next)
	//		get_put(select->next->mln->tern_next, &tres, select->next->mln->value);
	//	if (!select->next || !tres)
		reset_put(select->mln->tern_next);
		tmp = select->mln->tern_next->npsb;
		if (select->next)
			tmp += select->next->mln->tern_next->npsb;
		else if (select->prev)
			tmp += select->prev->mln->tern_next->npsb;
		if (tmp % (val + 1) != 0)
			*cpt += nb_col - (tmp % (nb_col + 1) - 1);
		deal_comp_key(select->mln->tern_next, val, cpt);
	}
	if (val == *cpt && !select->next)
	{
		*cpt = 0;
		get_put(select->mln->tern_next, &tres, select->mln->value);
		if (!tres)
		{
			reset_put(select->mln->tern_next);
			set_last_tree(select->mln->tern_next);
		}
	}

}

void	deal_slct_key(t_slct *select, int nb_col, int *cpt, int key)
{
	int		tmp;
	
	if (select->next)
		deal_slct_key(select->next, nb_col, cpt, key);
	if (select->down)
		deal_slct_key(select->down, nb_col, cpt, key);
	else
	{
		tmp = select->mln->tern_next->npsb;
		if (select->next)
			tmp += select->next->mln->tern_next->npsb;
		else if (select->prev)
			tmp += select->prev->mln->tern_next->npsb;
		if (key == DOWN)
			deal_slct_key_down(select, nb_col, cpt, nb_col);
		else if (key == UP)
		{
//			printf("nb_col : %d, tmp : %d, mod : %d\n", nb_col, tmp,  tmp % (nb_col + 1));
//			sleep(1);
			deal_slct_key_up(select, tmp - (nb_col - (tmp % (nb_col))), cpt, nb_col);
		}
	//	ft_putendl("");
	}
}


int		put_complet(char *str, t_tree *tern, char *tget, int *put, t_line *line, int *nb_ret)
{
	t_slct	*select;
	int		lenm;
	char	bru[257];
	char	*term;
	int		width;
	int		nb_col;
	int		car_ret;
	char	*chr;
	int		psb;
	int		tres;

	term = getenv("TERM");
	tgetent(NULL, term);
	width = tgetnum("co");
	lenm = 0;
	car_ret = 0;
	chr = NULL;
	select = NULL;
	psb = 0;
	tres = 0;
	if (!ft_strchr(str, ' '))
	{
		select = select_branch(tern, (chr = ft_strdup(str)), &lenm);
		if (!select)
		{
			free(chr);
			return (-1);
		}
	}
	else if (*(chr = !ft_strchr(ft_strrchr(str, ' '), '/')
				? ft_strdup(ft_strrchr(str, ' ') + 1)
				: ft_strdup(ft_strrchr(str, '/') + 1)))
	{
		if (!(select = select_branch(tern, chr, &lenm)))
		{
			free(chr);
			return (-1);
		}
	}
	else
		get_max_len(tern, &lenm);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	nb_col = width / (lenm + 1);
	if (select)
	{
		get_psb(select, ft_strlen(chr), 0, &psb);
		if (psb == 1)
		{
			if (!ft_strcmp(chr, str))
				ret_psb(select, ft_strlen(chr), 0, tget);
			else
				ret_psb(select, ft_strlen(chr), 0,
						!ft_strchr(ft_strrchr(tget, ' '), '/')
						? ft_strrchr(tget, ' ') + 1
						: ft_strrchr(tget, '/') + 1);
			free(chr);
			return (1);
		}
		int	cpt = 0;
		line->key = 1;
		if (line->is_putb == 2 && line->key)
		{
			deal_slct_key(select, nb_col - 1, &cpt, UP);
			//			tres = 0;
			//			get_isput(select, ft_strlen(chr), 1, &tres);
		}
		get_isput(select, ft_strlen(chr), 1, &tres);
		if (!tres)
			reset_isput(select, ft_strlen(chr), 1);
	}
	else
	{
		get_put(tern, &tres, *chr);
		if (!tres)
			reset_put(tern);
	}
	if (select)
	{
		put_branch(select, NULL, ft_strlen(chr), bru, 0,
				lenm, &car_ret, nb_col, put, tget, str, line, nb_ret);
	}
	else if (lenm)
		put_branch(NULL, tern, ft_strlen(chr), bru, 0,
				lenm, &car_ret, nb_col, put, tget, str, line, nb_ret);
	else
	{
		if (chr)
			free(chr);
		return (-1);
	}
	if (*line->e_cmpl & COMPLETION)
	{
		if (line->is_putb < 2)
			line->is_putb += 1;
	}
	*(line->e_cmpl) |= COMPLETION;
	if (chr)
		free(chr);
	return (0);
}

