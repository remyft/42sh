#include "../libft/include/libft.h"
#include <dirent.h>
#include <term.h>

typedef struct		s_tree
{
	int				value;
	int				max_len;
	int				tput;
	int				npsb;
	int				len;
	int				state;
	unsigned char	type;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*prev;
	struct s_tree	*tern_next;
}					t_tree;

typedef struct		s_select
{
	t_tree				*mln;
	struct s_select		*next;
	struct s_select		*down;
}					t_slct;

typedef struct		s_str_list
{
	char				*str;
	t_tree				*mln;
	int					state;
	struct s_str_list	*next;
	struct s_str_list	*prev;
}					t_slist;

# define IS_SLASH 1 << 0
# define IS_REC 1 << 1

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
		(*tern)->prev = prev->prev;
		if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
			(*tern)->max_len = lvl + len;
	}
	else
		if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
			(*tern)->max_len = lvl + len;
}

void	feed_tree(char *str, unsigned char type, t_tree **tern, int lvl)
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
		if (!*str)
		{
			(*tern)->len = lvl;
			(*tern)->type = type;
		}
		if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
			(*tern)->max_len = lvl + len;
	}
	if (!(*tern)->tern_next && *str)
	{
		(*tern)->tern_next = ft_memalloc(sizeof(t_tree));
		(*tern)->tern_next->prev = (*tern);
		(*tern)->tern_next->value = -1;
	}
	if (*str)
		feed_tree(str + 1, type, &((*tern)->tern_next), lvl + 1);
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
				feed_tree(indir->d_name, indir->d_type, ternary, 0);
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
		feed_tree(var, 0, ternary, 0);
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

void	put_branch2(t_slct *select, t_tree *tern, int len, char *bru, int lvl, int lenm, int *car_ret, int nb_col, int *put)
{
	if (tern)
		return (ft_put_tree(tern, bru, lvl, car_ret, nb_col, lenm, put));
	if (select && len > lvl + 1)
	{
		bru[lvl] = select->mln->value;
		put_branch2(select->down, tern,  len, bru, lvl + 1, lenm, car_ret, nb_col, put);
	}
	else if (select)
	{
		bru[lvl] = select->mln->value;
		bru[lvl + 1] = '\0';
		ft_put_tree(select->mln->tern_next, bru, lvl + 1, car_ret, nb_col, lenm, put);
	}
	if (select && select->next)
		put_branch2(select->next, tern, len, bru, lvl, lenm, car_ret, nb_col, put);
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
	char	*chr;

	term = getenv("TERM");
	tgetent(NULL, term);
	width = tgetnum("co");
	lenm = 0;
	put = 1;
	car_ret = 0;
	if (str && !ft_strchr(str, ' '))
	{
		select = select_branch2(tern, str, &lenm);
		nb_col = width / (lenm + 1);
		put_branch2(select, NULL, ft_strlen(str), bru, 0, lenm, &car_ret, nb_col, &put);
	}
	else
	{
		chr = !ft_strchr(ft_strrchr(str, ' '), '/') ? ft_strdup(ft_strrchr(str, ' ') + 1) : ft_strdup(ft_strrchr(str, '/') + 1);
		if (!(select = select_branch2(tern, str, &lenm)))
			get_max_len(tern, &lenm);
		if (select)
			put_branch2(select, NULL, ft_strlen(chr), bru, 0, lenm, &car_ret, nb_col, &put);
		else
			put_branch2(NULL, tern, ft_strlen(chr), bru, 0, lenm, &car_ret, nb_col, &put);
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

t_tree	*create_file_tree(char *path)
{
	struct dirent	*indir;
	DIR				*dir;
	char			prompt[4097];
	char			*tmp;
	t_tree			*tern;

	getcwd(prompt, 4097);
	if (path)
	{
		tmp = ft_strjoin(prompt, "/");
		path = ft_strjoinfree(tmp, path, 1);
	}
	else
		path = ft_strdup(prompt);
//	ft_putendl(path);
	dir = opendir(path);
	tern = ft_memalloc(sizeof(t_tree));
	tern->value = -1;
	while ((indir = readdir(dir)))
		//	if (indir->d_name[0] != '.')
		feed_tree(indir->d_name, indir->d_type, &tern, 0);
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

t_slist	*glob_slct(void)
{
	static t_slist *glob = NULL;

	if (!glob)
		glob = ft_memalloc(sizeof(t_slist));
	return (glob);
}

int		*singletint(void)
{
	static int	*state = NULL;

	if (!state)
		state = ft_memalloc(sizeof(int));
	return (state);
}

void	get_glob(t_tree *tree, char *tget, char *prev, t_slist **glob);

void	get_new_mln(t_tree *tree, char *str, char *prev, t_slist **glob)
{
	t_tree	*tmp;
	int		*sglt;
	int		tlen;
	char	*bru;
	DIR		*dir;

	tlen = 0;
	tmp = tree;
//	ft_putendl(str);
	while (1)
	{
		if (!tmp)
			return ;
		if (tmp->value != '.' && tmp->value != 0)
			break ;
		tmp = tmp->prev;
	}
/*	tmp = tree;
	while (tmp)
	{
		ft_putchar(tmp->value);
		tmp = tmp->prev;
	}
	ft_putnbr(i);
	ft_putendl("");*/
	sglt = singletint();
	if (*str == '/' && !(tree->type & DT_DIR) && !*(str + 1))
		return ;
	if (*str == '/')
		*sglt |= IS_SLASH;
/*	tmp = tree;
	while (tmp)
	{
		ft_putchar(tmp->value);
		tmp = tmp->prev;
	}
	ft_putnbr(i);
	ft_putendl("");*/
	if (*glob)
	{
		while ((*glob)->prev)
			*glob = (*glob)->prev;
		while ((*glob)->next && (*glob)->mln != tree)
			*glob = (*glob)->next;
		if ((*glob)->mln == tree)
			return ;
	//		printf("str : %s, tree : %p, glob : %p, lol : %d\n", glob->str, tree, glob->mln, lol);
		//printf("i : %d\n", i);
		(*glob)->next = ft_memalloc(sizeof(t_slist));
		(*glob)->next->prev = *glob;
		*glob = (*glob)->next;
	}
	else
		*glob = ft_memalloc(sizeof(t_slist));
	(*glob)->mln = tree;
	if (prev)
	{
//		printf("prev : %s, i : %d\n", prev, i);
		tlen = ft_strlen(prev) + 1;
	}
	tlen = (*glob)->mln->len + tlen;
//	ft_putstr("GET MALLOC : ");
	(*glob)->str = malloc(sizeof(char) * (tlen + 1));
	if (prev)
	{
//		printf("prev strcat  : %s, i : %d\n", prev, i);
		ft_strcpy((*glob)->str, prev);
		ft_strcat((*glob)->str, "/");
	}
	tmp = (*glob)->mln;
	(*glob)->str[tlen + 1] = 0;
	while (tmp)
	{
		(*glob)->str[tlen] = tmp->value;
		tmp = tmp->prev;
		tlen--;
	}
	bru = ft_strdup((*glob)->str);
	if ((dir = opendir((*glob)->str)) && ((*str == '/' && *(str + 1)) || *sglt & IS_REC))
	{
		if (!(tmp = create_file_tree((*glob)->str)))
			return ;
		*sglt |= IS_SLASH;
	//	printf("str : %s, prev : %s\n", glob->str, prev);
		if (*sglt & IS_REC)
			get_glob(tmp, "**", bru, glob);
		else
			get_glob(tmp, str + 1, bru, glob);
	}
	if (dir)
		closedir(dir);
}

void	get_glob(t_tree *tree, char *tget, char *prev, t_slist **glob)
{
	int	*sglt;

	sglt = singletint();
	if (tree)
	{
		get_glob(tree->left, tget, prev, glob);
		get_glob(tree->right, tget, prev, glob);
		if (!(tree->value) && *tget == '*')
		{
			if (*(tget + 1) == '*')
				if (*sglt & IS_SLASH)
					*sglt |= IS_REC;
			while (*tget == '*')
				tget++;
		}
		if ((!(*tget) || *tget == '/') && !(tree->value))
		{
			if (*tget == '/')
				*sglt |= IS_SLASH;
			while (*(tget + 1) == '/')
				tget++;
			get_new_mln(tree, tget, prev, glob);
		}
		else if (*tget == '*')
		{
			get_glob(tree->tern_next, tget, prev, glob);
			if (*(tget + 1) == '*')
				if (*sglt & IS_SLASH)
					*sglt |= IS_REC;
			while (*(tget + 1) == '*')
				tget++;
			if (*(tget+1) == tree->value)
				get_glob(tree, tget + 1, prev, glob);
		}
		else if (*tget == tree->value)
			get_glob(tree->tern_next, tget + 1, prev, glob);
	}
}

void	ft_nstrstr(char *str, char *to_find, int *nb)
{
	char	*ptr;

	if ((ptr = ft_strstr(str, to_find)))
	{
		if (ft_strlen(ptr) > ft_strlen(to_find))
		{
			if ((ptr = ft_strchr(ptr, '/')))
				*nb += 1;
			else
				return ;
			ft_nstrstr(ptr, to_find, nb);
		}
	}
}

int		ft_nslash(char *str)
{
	int		nb;
	int		i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
		{
			nb++;
			while (str[i] == '/')
				i++;
			if (!str[i])
				nb--;
		}
		else
			i++;
	}
	return (nb);
}

int		main(int ac, char **av, char **env)
{
	t_tree	*bin;
	t_tree	*files;
	t_tree	*save;
	t_slct	*select;
	t_slist	*glob = NULL;
	int		len;
	int		lenm;
	int		car_ret;
	char	*term;
	int		star;
	int		nb = 0;

	term = getenv("TERM");
	tgetent(NULL, term);
	//	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	bin = create_tree(env);
	files = create_file_tree(NULL);
	get_glob(files, av[1], NULL, &glob);
	/*	while (lst_glob)
		{
		if (lst_glob->mln)
		{
		if (!ret)
		ret = ft_memalloc(sizeof(t_slist));
		else
		{
		ret->next = ft_memalloc(sizeof(t_slist));
		ret->next->prev = ret;
		ret = ret->next;
		}
		len = lst_glob->mln->len;
		ret->str = ft_memalloc(sizeof(char) * (len + 1));
		while (lst_glob->mln)
		{
		ret->str[len] = lst_glob->mln->value;
		lst_glob->mln = lst_glob->mln->prev;
		len--;
		}
		}
		lst_glob = lst_glob->next;
		}*/
	star = 0;
//	if (ft_strstr(av[1], "**"))
//	{
		ft_nstrstr(av[1], "**", &star);
		nb = ft_nslash(av[1]);
		star = nb - star;
//		printf("star : %d, nb : %d\n", star, nb);
//	}
	while (glob && glob->prev)
		glob = glob->prev;
	while (glob && glob->str)
	{
		if (ft_occuc(glob->str, '/') >= star)
			ft_putendl(glob->str);
		glob = glob->next;
	}
	//	set_psblty(files);
	//	select = select_branch2(files, av[1], &lenm);
	//	if (select)
	//		put_select(select, 1);
	//	save = files;
	//	put_complet2(av[1], files);
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
