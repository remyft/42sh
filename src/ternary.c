/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 19:07:11 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/06 06:32:26 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (tern->tern_next && (tern->value != '.' || bru[0]))
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
					//	tget = replace_str(tget, ft_strrchr(tget, ' ') + 1, bru);
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

int		select_branch(t_tree **begin, t_tree **end, char *src)//, char *dst, char *strsave)
{
	int		lenm;
	int		i;
//	t_tree	*save;

	i = -1;
	lenm = 0;
	while (src[++i] && *begin)
	{
	//	save = *begin;
		while (*begin && (*begin)->value != ft_toupper(src[i]))
			*begin = ft_toupper(src[i]) < (*begin)->value ? (*begin)->left : (*begin)->right;
	/*	while (save && save->value != ft_tolower(src[i]))
			save = ft_tolower(src[i]) < save->value ? save->left : save->right;
		if (!*begin)
		{
			if (save)
			{
				*begin = save;
				dst[i] = ft_tolower(dst[i]);
				strsave[i] = dst[i];
			}
		}
		else if (!save)
		{
			src[i] = ft_toupper(src[i]);
			strsave[i] = src[i];
		}
		else
		{
			src[i] = ft_toupper(src[i]);
			dst[i] = ft_tolower(dst[i]);
		}*/
		if (*begin && !src[i + 1])
			lenm = (*begin)->max_len;
		if (*begin)
			(*begin) = (*begin)->tern_next;
	}
	i = -1;
	while (src[++i] && *end)
	{
		while (*end && (*end)->value != ft_tolower(src[i]))
			*end = ft_tolower(src[i]) < (*end)->value ? (*end)->left : (*end)->right;
		if (*end && !src[i + 1])
			lenm = (*end)->max_len > lenm ? (*end)->max_len : lenm;
		if ((*end))
			*end = (*end)->tern_next;
	}
	return (lenm);
}

void	put_branch(t_tree *tern, char *src, int lenm, int *car_ret, int *put, char *tget, char *old)
{
	char	bru[257];
	char	*term;
	int		width;
	int		nb_col;
	int		lvl;

	term = getenv("TERM");
	tgetent(NULL, term);
	width = tgetnum("co");
	nb_col = width / (lenm + 1);
	if (tern)
	{
		lvl = ft_strlen(src);
	//	ft_putendl(src);
		if (src)
			ft_strcpy(bru, src);
		ft_put_tree(tern, bru, lvl, car_ret, nb_col, lenm, put, tget, old);
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

int		put_complet(char *str, t_tree *tern, char *tget, int *put)
{
	int		lenm;
	int		car_ret;
	t_tree	*begin;
	int		tres;
	char	*tmp;
	char	*chr;
//	char	*chr2;

	begin = tern;
	car_ret = 0;
	tres = 0;
	lenm = 0;
	if (!str)
		tmp = ft_strnew(1);
		//ft_bzero(tmp, 8192);
	else
		tmp = ft_strdup(str);
		//ft_strcpy(tmp, str);
	if (str && !ft_occuc(str, ' '))
	{
		lenm = select_branch(&begin, &tern, tmp);//, tget, tget);
		if (begin)
		{
			if (!tern && begin->npsb == 1)
				return (get_tstr(begin, tget));
			get_put(begin, &tres, *str);
		}
		if (tern && tern != begin)
		{
			if (!begin && tern->npsb == 1)
				return (get_tstr(tern, tget));
			get_put(tern, &tres, *str);
		}
		if (!tres)
		{
			if (begin)
				reset_put(begin);
			if (tern && tern != begin)
				reset_put(tern);
		}
		if (begin)
			put_branch(begin, ft_strup(tmp, ft_strlen(tmp)), lenm, &car_ret, put, tget, str);
		if (tern && tern != begin)
			put_branch(tern, ft_strlow(tmp, ft_strlen(tmp)), lenm, &car_ret, put, tget, str);
	}
	else if (!ft_occuc(ft_strrchr(tmp, ' ') + 1, '/'))
	{
		if (*(chr = ft_strdup((ft_strrchr(tmp, ' ') + 1))))
	//	{
	//		chr2 = ft_strdup(ft_strrchr(tmp, ' ') + 1);
			lenm = select_branch(&begin, &tern, chr);//, chr2, ft_strrchr(tget, ' ') + 1);
	//	}
		else
			get_max_len(begin, &lenm);
		if (begin)
		{
			if ((!tern || begin == tern) && begin->npsb == 1)
				return (get_tstr(begin, tget));
			get_put(begin, &tres, *chr);
		}
		if (tern && tern != begin)
		{
			if (!begin && tern->npsb == 1)
				return (get_tstr(tern, tget));
			get_put(tern, &tres, *chr);
		}
		if (!tres)
		{
			if (begin)
				reset_put(begin);
			if (tern && tern != begin)
				reset_put(tern);
		}
		//get_max_len(begin, &lenm);
		if (begin)
			put_branch(begin, ft_strup(chr, ft_strlen(chr)), lenm, &car_ret, put, tget, str);
		if (*chr && tern && tern != begin)
			put_branch(tern, ft_strlow(chr, ft_strlen(chr)), lenm, &car_ret, put, tget, str);
	}
	else
	{
		if (*(chr = (ft_strrchr(tmp, '/') + 1)))
			lenm = select_branch(&begin, &tern, chr);//, ft_strrchr(tget, '/') + 1, ft_strrchr(tget, '/') + 1);
		else
			get_max_len(begin, &lenm);
		if (begin)
		{
			if ((!tern || begin == tern) && begin->npsb == 1)
				return (get_tstr(begin, tget));
			get_put(begin, &tres, *chr);
		}
		if (tern && tern != begin)
		{
			if (!begin && tern->npsb == 1)
				return (get_tstr(tern, tget));
			get_put(tern, &tres, *chr);
		}
		if (!tres)
		{
			if (begin)
				reset_put(begin);
			if (tern && tern != begin)
				reset_put(tern);
		}
		//get_max_len(begin, &lenm);
		if (begin)
			put_branch(begin, ft_strup(chr, ft_strlen(chr)), lenm, &car_ret, put, tget, str);
		if (*chr && tern && tern != begin)
			put_branch(tern, ft_strlow(chr, ft_strlen(chr)), lenm, &car_ret, put, tget, str);

	}
	free(tmp);
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

void	free_tree(t_tree *tern)
{
	if (tern->left)
		free_tree(tern->left);
	if (tern->right)
		free_tree(tern->right);
	if (tern->tern_next)
		free_tree(tern->tern_next);
	if (tern)
	{
		free(tern);
		tern = NULL;
	}
}
