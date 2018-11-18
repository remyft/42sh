/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 19:07:11 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/18 03:21:52 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_psblty(t_tree *tern, int *nb)
{
	if (tern->right)
		get_psblty(tern->right, nb);
	if (tern->left)
		get_psblty(tern->left, nb);
	if (tern->tern_next)
		get_psblty(tern->tern_next, nb);
	if (!tern->tern_next)
		*nb += 1;
}

void	set_psblty(t_tree *tern)
{
	if (tern->right)
		set_psblty(tern->right);
	if (tern->left)
		set_psblty(tern->left);
	if (tern->tern_next)
	{
		set_psblty(tern->tern_next);
		//get_psblty(tern->tern_next, &(tern->npsb));
	}
	get_psblty(tern, &(tern->npsb));
}

void	feed_branch(t_tree **tern, char *str, int lvl)
{
	t_tree	*prev;
	int		len;

	prev = NULL;
	while (*tern && (*tern)->value != *str)
	{
		prev = *tern;
		(*tern) = (*str < (*tern)->value) ? (*tern)->left : (*tern)->right;
	}
	if (!(*tern))
	{
		*tern = ft_memalloc(sizeof(t_tree));
		if (*str < prev->value)
			prev->left = *tern;
		else
			prev->right = *tern;
		(*tern)->value = *str;
		if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
			(*tern)->max_len = lvl + len;
	}
	else
		if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
			(*tern)->max_len = lvl + len;
}

void	feed_tree(char *str, t_tree **tern, int lvl)
{
	t_tree		*begin;
	int			len;

	begin = NULL;
	if ((*tern)->value >= 0)
	{
		begin = *tern;
		feed_branch(tern, str, lvl);
	}
	else
	{
		(*tern)->value = *str;
		if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
			(*tern)->max_len = lvl + len;
	}
	if (!(*tern)->tern_next && *str)
	{
		(*tern)->tern_next = ft_memalloc(sizeof(t_tree));
		(*tern)->tern_next->value = -1;
	}
	if (*str)
		feed_tree(str + 1, &((*tern)->tern_next), lvl + 1);
	*tern = begin ? begin : *tern;
}

void	ft_putchars(char c, int nb)
{
	while (nb--)
		ft_putchar(c);
}

void	ft_put_tree(t_tree *tern, char *bru, int lvl, int *car_ret, int nb_col, int len_max, int *put, char *tget, char *old)
{
	char	*chr;
	int		i;

	if (tern->left)
		ft_put_tree(tern->left, bru, lvl, car_ret, nb_col, len_max, put, tget, old);
	if (tern->tern_next && (tern->value != '.' || bru[0] == '.' || lvl >= 1))
	{
		bru[lvl] = tern->value;
		ft_put_tree(tern->tern_next, bru, lvl + 1, car_ret, nb_col, len_max, put, tget, old);
	}
	if (tern && !tern->tern_next)
	{
		bru[lvl] = '\0';
		if (!tern->tput && *put)
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
		ft_put_tree(tern->right, bru, lvl, car_ret, nb_col, len_max, put, tget, old);
}

void	get_max_len(t_tree *curr, int *lenm)
{
	if (curr->left)
		get_max_len(curr->left, lenm);
	if (curr->right)
		get_max_len(curr->right, lenm);
	if (curr->max_len > *lenm)
		*lenm = curr->max_len;
}

void	fill_tree_bin(char **env, t_tree **ternary)
{
	char			*toget;
	struct dirent	*indir;
	DIR				*dir;
	int				i;
	char			*path;

	toget = get_env(env, "PATH");
	*ternary = ft_memalloc(sizeof(t_tree));
	(*ternary)->value = -1;
	i = 0;
	while (1)
	{
		path = strdup_until(&toget[i], ':');
		dir = opendir(path);
		free(path);
		while ((indir = readdir(dir)))
			if (ft_strcmp(indir->d_name, ".") && ft_strcmp(indir->d_name, ".."))
				feed_tree(indir->d_name, ternary, 0);
		if (!ft_occuc(&toget[i], ':'))
			break ;
		i += !(toget[i + ft_strlen_ch(toget, ':')])
			? ft_strlen_ch(&toget[i], ':') : ft_strlen_ch(&toget[i], ':') + 1;
		closedir(dir);
	}
	if (dir)
		closedir(dir);
	free(toget);
}

void	fill_tree_env(char **env, t_tree **ternary)
{
	int		i;
	char	*var;

	i = 0;
	while (env[i])
	{
		var = strdup_until(env[i], '=');
		feed_tree(var, ternary, 0);
		free(var);
		i++;
	}
}

t_tree	*create_tree(char **env)
{
	t_tree	*ternary;

	if (!env)
		return (NULL);
	ternary = NULL;
	fill_tree_bin(env, &ternary);
	fill_tree_env(env, &ternary);
	set_psblty(ternary);
	return (ternary);
}

void	reset_put(t_tree *tern)
{
	if (tern->left)
		reset_put(tern->left);
	if (tern->right)
		reset_put(tern->right);
	if (tern->tern_next)
		reset_put(tern->tern_next);
	if (tern && !tern->tern_next)
		tern->tput = 0;
}

void	deal_reset(t_tree *tree1, t_tree *tree2, t_tree *tree3)
{
	if (tree1)
		reset_put(tree1);
	if (tree2)
		reset_put(tree2);
	if (tree3)
		reset_put(tree3);
}

void	get_put(t_tree *tern, int *ret, char c)
{
	if (tern->left)
		get_put(tern->left, ret, c);
	if (tern->right)
		get_put(tern->right, ret, c);
	if (tern->tern_next && (tern->value != '.' || c))
		get_put(tern->tern_next, ret, 1);
	if (tern && !tern->tern_next)
		if (tern->tput == 0)
			*ret = 1;
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

int		get_tstr(t_tree *tern, char *str)
{
	int i;

	i = ft_strlen(str);
	while (tern)
	{
		str[i++] = tern->value;
		tern = tern->tern_next;
	}
	return (1);
}

void	put_branch(t_slct *select, t_tree *tern, int len, char *bru, int lvl, int lenm, int *car_ret, int nb_col, int *put, char *tget, char *old)
{
	if (tern)
		return (ft_put_tree(tern, bru, lvl, car_ret, nb_col, lenm, put, tget, old));
	if (select && len > lvl + 1)
	{
		bru[lvl] = select->mln->value;
		put_branch(select->down, tern,  len, bru, lvl + 1, lenm, car_ret, nb_col, put, tget, old);
	}
	else if (select)
	{
		bru[lvl] = select->mln->value;
		bru[lvl + 1] = '\0';
		ft_put_tree(select->mln->tern_next, bru, lvl + 1, car_ret, nb_col, lenm, put, tget, old);
	}
	if (select && select->next)
		put_branch(select->next, tern, len, bru, lvl, lenm, car_ret, nb_col, put, tget, old);
}

void	get_isput(t_slct *select, int len, int lvl, int *tres)
{
	if (select->next)
		get_isput(select->next, len, lvl, tres);
	if (select->down)
		get_isput(select->down, len, lvl + 1, tres);
	else if (lvl == len)
		get_put(select->mln->tern_next, tres, select->mln->value);
}

void	reset_isput(t_slct *select, int len, int lvl)
{
	if (select->next)
		reset_isput(select->next, len, lvl);
	if (select->down)
		reset_isput(select->down, len, lvl + 1);
	else if (lvl == len)
		reset_put(select->mln->tern_next);
}

void	get_psb(t_slct *select, int len, int lvl, int *psb)
{
	if (select->next)
		get_psb(select->next, len, lvl, psb);
	if (select->down)
		get_psb(select->down, len, lvl + 1, psb);
	else if (lvl + 1 == len)
		if (select->mln->npsb)
			*psb += select->mln->tern_next->npsb;
}

int		ret_psb(t_slct *select, int len, int lvl, char *bru)
{
	if (select->next)
		if (ret_psb(select->next, len, lvl, bru))
			return (1);
	if (select->down)
	{
		bru[lvl] = select->mln->value;
		if (ret_psb(select->down, len, lvl + 1, bru))
			return (1);
	}
	else if (lvl + 1 == len)
		if (select->mln->npsb)
		{
			bru[lvl] = '\0';
			get_tstr(select->mln, bru);
			return (1);
		}
	return (0);
}

void	put_select(t_slct *select, int lvl)
{
	if (select->next)
		put_select(select->next, lvl);
	if (select->down)
		put_select(select->down, lvl + 1);
}

int		put_complet(char *str, t_tree *tern, char *tget, int *put)
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
	else if (*(chr = !ft_strchr(ft_strrchr(str, ' '), '/') ? ft_strdup(ft_strrchr(str, ' ') + 1) : ft_strdup(ft_strrchr(str, '/') + 1)))
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
				ret_psb(select, ft_strlen(chr), 0, !ft_strchr(ft_strrchr(tget, ' '), '/') ? ft_strrchr(tget, ' ') + 1 : ft_strrchr(tget, '/') + 1);
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
		put_branch(select, NULL, ft_strlen(chr), bru, 0, lenm, &car_ret, nb_col, put, tget, str);
	else if (lenm)
		put_branch(NULL, tern, ft_strlen(chr), bru, 0, lenm, &car_ret, nb_col, put, tget, str);
	else
	{
		if (chr)
			free(chr);
		return (-1);
	}
	if (chr)
		free(chr);
	return (0);
}

t_tree	*create_file_tree(char *path)
{
	struct dirent	*indir;
	DIR				*dir;
	t_tree			*tern;

	if (!path)
		return (NULL);
	if (!(dir = opendir(path)))
		return (NULL);
	tern = ft_memalloc(sizeof(t_tree));
	tern->value = -1;
	while ((indir = readdir(dir)))
		feed_tree(indir->d_name, &tern, 0);
	set_psblty(tern);
	closedir(dir);
	return (tern);
}

void	*free_tree(t_tree *tern)
{
	if (tern)
	{
		if (tern->left)
			free_tree(tern->left);
		if (tern->right)
			free_tree(tern->right);
		if (tern->tern_next)
			free_tree(tern->tern_next);
		free(tern);
	}
	return (NULL);
}

static int		deal_complet(t_tree *file, char *buff, char *buff_tmp, char *tmp, int *i, t_st *e_cmpl)
{
	int		put;
	int		j;
	char	prompt[4097];

	*e_cmpl |= COMPLETION;
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	if (!buff_tmp[8193])
	{
		ft_strcpy(buff_tmp, buff);
		buff_tmp[8193] = 1;
	}
	else
		put = 1;
	if ((put = put_complet(buff_tmp, file, buff, &put)) == 1)
		tmp[0] = 10;
	else if (put == -1)
	{
		*e_cmpl &= ~COMPLETION;
		tmp[0] = 0;
	}
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3), 1, ft_pchar);
	j = -1;
	while (++j < *i)
		tputs(tgetstr("dc", NULL), 1, ft_pchar);
	ft_putstr(buff);
	*i = ft_strlen(buff);
	return (*i);
}

int		set_complet(t_tree **file, t_st *e_cmpl, char *tmp, char *buff, int *i, char *buff_tmp)
{
	DIR		*dir;

	dir = NULL;
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
	*e_cmpl &= ~COMPLETION;
	tmp[0] = 0;
	if (ft_strrchr(buff, ' ') && (dir = opendir(ft_strrchr(buff, ' ') + 1)))
	{
		if (*file)
			free_tree(*file);
		*file = NULL;
		buff[(*i)] = '/';
		buff[++(*i)] = '\0';
		ft_putchar('/');
	}
	else
	{
		buff[(*i)++] = ' ';
		buff[++(*i)] = '\0';
		ft_putchar(' ');
	}
	if (dir)
		closedir(dir);
	ft_bzero(buff_tmp, 8194);
	return (*i);
}

t_tree	*set_tmp(char *buff)
{
	t_tree	*file;
	char	*stmp;

	stmp = ft_strrchr(buff, ' ') + 1;
	stmp = ft_strndup(stmp, ft_strrchr(stmp, '/') - stmp);
	file = create_file_tree(stmp);
	free(stmp);
	return (file);
}

int		inprint(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (ft_isprint(str[i]))
			return(1);
	return (0);
}

void	get_complet(t_line *line)
{
	if (!inprint(line->buff))
		return ;
	if (!ft_strchr(line->buff, ' ') || !ft_strchr(ft_strrchr(line->buff, ' '), '/'))
		line->index = deal_complet(!ft_strchr(line->buff, ' ') ? line->tree[0] : line->tree[1], line->buff, line->buff_tmp, line->tmp, &(line->len), line->e_cmpl);
	else
		if (line->tree[2] || (line->tree[2] = set_tmp(line->buff)))
			line->index = deal_complet(line->tree[2], line->buff, line->buff_tmp, line->tmp, &(line->len), line->e_cmpl);
}
