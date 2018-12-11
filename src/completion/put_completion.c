/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:42:34 by rfontain          #+#    #+#             */
/*   Updated: 2018/12/11 17:50:21 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "put.h"

void	ft_put_tree(t_tree *tern, char *bru, int lvl, int *car_ret, int nb_col, int len_max, int *put, char *tget, char *old, t_line *line)
{
	char	*chr;
	int		i;

	if (tern->left)
		ft_put_tree(tern->left, bru, lvl, car_ret, nb_col, len_max, put, tget, old, line);
	if (tern->tern_next && (tern->value != '.' || bru[0] == '.' || lvl >= 1))
	{
		bru[lvl] = tern->value;
		ft_put_tree(tern->tern_next, bru, lvl + 1, car_ret, nb_col, len_max, put, tget, old, line);
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
		ft_putchar(tern->value);
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
		}
	}
	if (tern->right)
		ft_put_tree(tern->right, bru, lvl, car_ret, nb_col, len_max, put, tget, old, line);
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
			select->down = select_branch(upper->tern_next, src + 1, lenm);
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
				select->next->mln = lower;
				select->next->down = select_branch(lower->tern_next, src + 1, lenm);
			}
			else
			{
				select = ft_memalloc(sizeof(t_slct));
				select->mln = lower;
				if (*(src + 1) && !(select->down) && !(select->down = select_branch(lower->tern_next, src + 1, lenm)))
					return (NULL);
			}
		}
	}
	return (select);
}

void	put_branch(t_slct *select, t_tree *tern, int len, char *bru, int lvl, int lenm, int *car_ret, int nb_col, int *put, char *tget, char *old, t_line *line)
{
	if (tern)
		return (ft_put_tree(tern, bru, lvl, car_ret, nb_col, lenm, put, tget, old, line));
	if (select && len > lvl + 1)
	{
		bru[lvl] = select->mln->value;
		put_branch(select->down, tern,  len, bru, lvl + 1, lenm, car_ret, nb_col, put, tget, old, line);
	}
	else if (select)
	{
		bru[lvl] = select->mln->value;
		bru[lvl + 1] = '\0';
		ft_put_tree(select->mln->tern_next, bru, lvl + 1, car_ret, nb_col, lenm, put, tget, old, line);
	}
	if (select && select->next)
		put_branch(select->next, tern, len, bru, lvl, lenm, car_ret, nb_col, put, tget, old, line);
}


int		put_complet(char *str, t_tree *tern, char *tget, int *put, t_line *line)
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
		select = select_branch(tern, (chr = ft_strdup(str)), &lenm);
	else if (*(chr = !ft_strchr(ft_strrchr(str, ' '), '/')
				? ft_strdup(ft_strrchr(str, ' ') + 1)
					: ft_strdup(ft_strrchr(str, '/') + 1)))
		select = select_branch(tern, chr, &lenm);
	else
		get_max_len(tern, &lenm);
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
	nb_col = width / (lenm + 1);
	if (select)
		put_branch(select, NULL, ft_strlen(chr), bru, 0,
				lenm, &car_ret, nb_col, put, tget, str, line);
	else if (lenm)
		put_branch(NULL, tern, ft_strlen(chr), bru, 0,
				lenm, &car_ret, nb_col, put, tget, str, line);
	else
	{
		if (chr)
			free(chr);
		return (-1);
	}
	*(line->e_cmpl) |= COMPLETION;
	if (chr)
		free(chr);
	return (0);
}

