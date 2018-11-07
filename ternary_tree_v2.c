#include "libft/libft.h"
#include <dirent.h>
#include <term.h>

typedef struct		s_tree
{
	int				value;
	int				max_len;
	int				tput;
	int				npsb;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*tern_next;
}					t_tree;

typedef struct		s_select
{
	t_tree				*mln;
	struct s_select		*next;
	struct s_select		*down;
}					t_slct;

int			ft_pchar(int nb)
{
	return (write(STDOUT_FILENO, &nb, 1));
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
	t_tree		*prev;
	t_tree		*tmp;
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

char		*ft_tgetstr(char *t)
{
	char            *tmp;

	if ((tmp = tgetstr(t, NULL)) == NULL)
	{
		ft_putstr_fd(t, 2);
		ft_putendl_fd(" not available", 2);
	}
	return (tmp);
}

void	ft_put_tree(t_tree *tern, char *bru, int lvl, int *car_ret, int nb_col, int len_max, int *put)
{
	if (tern->left)
		ft_put_tree(tern->left, bru, lvl, car_ret, nb_col, len_max, put);
	if (tern->tern_next)
	{
		bru[lvl] = tern->value;
		ft_put_tree(tern->tern_next, bru, lvl + 1, car_ret, nb_col, len_max, put);
	}
	if (tern && !tern->tern_next)
	{
		bru[lvl] = '\0';
		if (!tern->tput && *put)
		{
			tputs(ft_tgetstr("mr"), 1, ft_pchar);
			tern->tput = 1;
			*put = 0;
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
			ft_putchar('\n');
			*car_ret = 0;
		}
	}
	if (tern->right)
		ft_put_tree(tern->right, bru, lvl, car_ret, nb_col, len_max, put);
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

	toget = getenv("PATH");
	*ternary = ft_memalloc(sizeof(t_tree));
	(*ternary)->value = -1;
	i = 0;
	while (1)
	{
		path = strdup_until(&toget[i], ':');
		dir = opendir(path);
		while ((indir = readdir(dir)))
			if (ft_strcmp(indir->d_name, ".") && ft_strcmp(indir->d_name, ".."))
				feed_tree(indir->d_name, ternary, 0);
		if (!ft_occuc(&toget[i], ':'))
			break ;
		i += !(toget[i + ft_strlen_ch(toget, ':')])
			? ft_strlen_ch(&toget[i], ':') : ft_strlen_ch(&toget[i], ':') + 1;
	}
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

t_slct		*select_branch2(t_tree *upper, char *src, int *lenm)
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
			select->down = select_branch2(upper->tern_next, src + 1, lenm);
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
				select->next->down = select_branch2(lower->tern_next, src + 1, lenm);
			}
			else
			{
				select = ft_memalloc(sizeof(t_slct));
				select->mln = lower;
				if (*(src + 1) && !(select->down) && !(select->down = select_branch2(lower->tern_next, src + 1, lenm)))
					return (NULL);
			}
		}
	}
	return (select);
}


int		select_branch(t_tree **begin, t_tree **end, char *src)
{
	int		lenm;
	int		i;
	t_tree	*save;

	i = -1;
	while (src[++i] && *begin)
	{
		save = *begin;
		while (*begin && (*begin)->value != ft_toupper(src[i]))
			*begin = ft_toupper(src[i]) < (*begin)->value ? (*begin)->left : (*begin)->right;
		if (!*begin)
		{
			while (save && save->value != ft_tolower(src[i]))
				save = ft_tolower(src[i]) < save->value ? save->left : save->right;
			if (save)
				*begin = save;
		}
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

void	put_branch(t_tree *tern, char *src, int lenm, int *car_ret, int *put)
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
		if (src)
			ft_strcpy(bru, src);
		ft_put_tree(tern, bru, lvl, car_ret, nb_col, lenm, put);
	}
}

t_tree	*create_tree(char **env)
{
	t_tree	*ternary;

	ternary = NULL;
	fill_tree_bin(env, &ternary);
	fill_tree_env(env, &ternary);
	return (ternary);
}

void	put_branch2(t_slct *select, int len, char *bru, int lvl, int lenm, int *car_ret, int nb_col, int *put)
{
	if (select && len > lvl + 1)
	{
		bru[lvl] = select->mln->value;
		put_branch2(select->down, len, bru, lvl + 1, lenm, car_ret, nb_col, put);
	}
	else if (select)
	{
		bru[lvl] = select->mln->value;
		bru[lvl + 1] = '\0';
		ft_put_tree(select->mln->tern_next, bru, lvl + 1, car_ret, nb_col, lenm, put);
	}
	if (select && select->next)
		put_branch2(select->next, len, bru, lvl, lenm, car_ret, nb_col, put);
}

void	put_complet2(char *str, t_tree *tern)
{
	t_slct	*select;
	int		lenm;
	char	bru[257];
	char	*term;
	int		width;
	int		nb_col;
	int		car_ret;
	int		put;

	term = getenv("TERM");
	tgetent(NULL, term);
	width = tgetnum("co");
	lenm = 0;
	put = 1;
	car_ret = 0;
	if (str && *str)
	{
		select = select_branch2(tern, str, &lenm);
		nb_col = width / (lenm + 1);
		put_branch2(select, ft_strlen(str), bru, 0, lenm, &car_ret, nb_col, &put);
	}
}

void	put_complet(char *str, t_tree *tern)
{
	int		lenm;
	int		car_ret;
	t_tree	*begin;
	int		put;

	begin = tern;
	car_ret = 0;
	put = 1;
	lenm = 0;
	if (str && *str)
	{
		lenm = select_branch(&begin, &tern, str);
		put_branch(begin, ft_strup(str, ft_strlen(str)), lenm, &car_ret, &put);
		put_branch(tern, ft_strlow(str, ft_strlen(str)), lenm, &car_ret, &put);
	}
	else
	{
		get_max_len(tern, &lenm);
		put_branch(tern, NULL, lenm, &car_ret, &put);
	}
}

t_tree	*create_file_tree(void)
{
	struct dirent	*indir;
	DIR				*dir;
	char			prompt[4097];
	t_tree			*tern;

	dir = opendir(getcwd(prompt, 4097));
	tern = ft_memalloc(sizeof(t_tree));
	tern->value = -1;
	while ((indir = readdir(dir)))
	//	if (indir->d_name[0] != '.')
			feed_tree(indir->d_name, &tern, 0);
	return (tern);
}

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
		get_psblty(tern->tern_next, &(tern->npsb));
	}
	//	get_psblty(tern, &(tern->npsb));
}

void	put_psb(t_tree *tern)
{
	if (tern->right)
		put_psb(tern->right);
	if (tern->left)
		put_psb(tern->left);
	if (tern->tern_next)
		put_psb(tern->tern_next);
	ft_putchar(tern->value);
	ft_putstr(" : ");
	ft_putnbend(tern->npsb, "\n");
}

void	put_select(t_slct *select, int lvl)
{
	ft_putchar(select->mln->value);
	ft_putnbr(lvl);
	ft_putendl("");
	if (select->next)
		put_select(select->next, lvl);
	if (select->down)
	{
		ft_putchar(select->mln->value);
		put_select(select->down, lvl + 1);
	}
}

int		main(int ac, char **av, char **env)
{
	t_tree	*bin;
	t_tree	*files;
	t_tree	*save;
	t_slct	*select;
	int		lenm;
	int		car_ret;
	char	*term;

	term = getenv("TERM");
	tgetent(NULL, term);
	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	bin = create_tree(env);
	files = create_file_tree();
//	set_psblty(files);
	select = select_branch2(bin, av[1], &lenm);
	if (select)
		put_select(select, 1);
	save = files;
	put_complet2(av[1], bin);
//	select_branch(&files, &save, av[1]);
/*	if (!files && !save)
	if (files)
	put_psb(files);
	if (save)
		put_psb(save);*/
/*	save = bin;
	if (av[1] && !av[2])
	{
		put_complet(av[1], bin);
		put_complet(av[1], save);
	}
	else if (av[1] && av[2])
		put_complet(av[2], files);
	else
		put_complet(av[1], bin);
	ft_putchar('\n');*/
	return (0);
}
