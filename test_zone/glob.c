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

typedef struct		s_stint
{
	char			*str;
	int				nb;
}					t_stint;

typedef struct		s_strlst
{
	char			*str;
	struct s_strlst	*prev;
	struct s_strlst	*next;
}					t_slst;

# define IS_SLASH 1 << 0
# define IS_STAR 1 << 1
# define IS_REC 1 << 2
# define IS_MARK 1 << 3

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
	lvl = 0;
	if (tern)
	{
		if (src)
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

int		ft_is_noalnum(char *str)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '*' || str[i] == '/' || str[i] == '?')
			count++;
		i++;
	}
	if (i == count)
		return (1);
	return (0);
}

void	get_glob(t_tree *tree, char *tget, t_slist **glob, t_stint sti);

int		check_list(t_tree *tree)
{
	t_tree *tmp;

	tmp = tree;
	while (tmp)
	{
		if (tmp->value != '.' && tmp->value != 0)
			return (1);
		tmp = tmp->prev;
	}
	return (0)
}

void	get_new_str(t_tree *tree, t_slist **glob, char *prev)
{
	int		tlen;
	t_tree	*tmp;

	tlen = 0;
	if (prev)
		tlen = ft_strlen(prev) + 1;
	tlen = (*glob)->mln->len + tlen;
	(*glob)->str = malloc(sizeof(char) * (tlen + 1));
	if (prev)
	{
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
}

int		get_new_glob(t_tree *tree, t_slist **glob)
{
	if (*glob)
	{
		while ((*glob)->prev)
			*glob = (*glob)->prev;
		while ((*glob)->next && (*glob)->mln != tree)
			*glob = (*glob)->next;
		if ((*glob)->mln == tree)
		{
			return (0);
		}
		(*glob)->next = ft_memalloc(sizeof(t_slist));
		(*glob)->next->prev = *glob;
		*glob = (*glob)->next;
	}
	else
		*glob = ft_memalloc(sizeof(t_slist));
	(*glob)->mln = tree;
	return (1);
}

void	deal_rec(t_tree *tree, char *str, t_slist **glob, t_stint *sti)
{
	t_tree *tmp;

	if (!(tmp = create_file_tree((*glob)->str)))
		return ;
	if (sti->nb & IS_SLASH)
		sti->nb |= IS_REC;
	if (sti->nb & IS_REC)
		get_glob(tmp, "**", glob, *sti);
	else
		get_glob(tmp, str + 1, glob, *sti);
}

void	get_new_mln(t_tree *tree, char *str, t_slist **glob, t_stint sti)
{
	t_tree	*tmp;
	char	*bru;
	DIR		*dir;
	t_stint	si_tmp;

	if (!check_list(tree))
		return ;
	if (*str == '/' && !(tree->type & DT_DIR) && !*(str + 1))
		return ;
	if (*str == '/' && sti.nb & IS_SLASH)
		sti.nb |= IS_REC;
	if (!get_new_glob(tree, glob))
		return ;
	get_new_str(tree, glob, sti.str);
	si_tmp.str = ft_strdup((*glob)->str);
	si_tmp.nb = sti.nb;
	if ((dir = opendir((*glob)->str)) && ((*str == '/' && *(str + 1)) || sti.nb & IS_REC))
		deal_rec(tree, str, glob, &si_tmp);
	free(si_tmp.str);
	if (dir)
		closedir(dir);
}

void	rev_brack(t_tree *tree, char *tget, t_slist **glob, t_stint sti)
{
	int		tmp;

	while (*tget && *tget != ']')
	{
		if (*tget == tree->value)
			return ;
		else if (*(tget + 1) == '-')
		{
			tmp = *tget;
			while (tmp < *(tget + 2))
			{
				if (tmp == tree->value)
					return ;
				tmp++;
			}
			tget += 2;
			if (*tget == tree->value)
				return ;
		}
		tget += 1;
	}
	get_glob(tree->tern_next, tget + 1, glob, sti);
}

void	norm_brack(t_tree *tree, char *tget, t_slist **glob, t_stint sti)
{
	int		tmp;

	while (*tget && *tget != ']')
	{
		if (*tget == tree->value)
		{
			while (*tget && *tget != ']')
				tget++;
			if (*tget != ']')
				return ;
			get_glob(tree->tern_next, tget + 1, glob, sti);
		}
		else if (*tget == '-')
			while (++tmp < *(tget + 1))
				if (tmp == tree->value)
				{
					while (*tget && *tget != ']')
						tget++;
					if (*tget != ']')
						return ;
					get_glob(tree->tern_next, tget + 1, glob, sti);
				}
		tget++;
		tmp = *tget - 1;
	}
}

int		glob_brack(t_tree *tree, char *tget, t_slist **glob, t_stint sti)
{
	int		tmp;

	if (*(tget + 1) == '!')
		rev_brack(tree, tget + 2, glob, sti);
	else
		norm_brack(tree, tget, glob, sti);
	return (1);
}

void	glob_star(t_tree *tree, char **tget, t_slist **glob, t_stint *sti)
{
	get_glob(tree->tern_next, *tget, glob, *sti);
	if (*(*tget + 1) == '*')
		sti->nb |= IS_SLASH;
	while (*(*tget + 1) == '*')
		*tget += 1;
	if (*(*tget + 1) == '?' || *(*tget + 1) == '[' || *(*tget + 1) == tree->value)
	{
		sti->nb &= ~IS_SLASH;
		get_glob(tree, *tget + 1, glob, *sti);
	}
}

void	glob_slash(t_tree *tree, char **tget, t_slist **glob, t_stint *sti)
{
	if (**tget == '/' && sti->nb & IS_SLASH)
		sti->nb |= IS_REC;
	while (*(*tget + 1) == '/')
		*tget += 1;
	get_new_mln(tree, *tget, glob, *sti);
}

void	get_glob(t_tree *tree, char *tget, t_slist **glob, t_stint sti)
{
	if (!tree)
		return ;
	get_glob(tree->left, tget, glob, sti);
	get_glob(tree->right, tget, glob, sti);
	if (!(tree->value) && *tget == '*')
	{
		if (*(tget + 1) == '*')
			sti.nb |= IS_SLASH;
		while (*tget == '*')
			tget++;
	}
	if ((!(*tget) || *tget == '/') && !(tree->value))
		glob_slash(tree, &tget, glob, &sti);
	else if (*tget == '*')
		glob_star(tree, &tget, glob, &sti);
	else if (*tget == tree->value)
		get_glob(tree->tern_next, tget + 1, glob, sti);
	else if (*tget == '?' && tree->value)
		get_glob(tree->tern_next, tget + 1, glob, sti);
	else if (*tget == '[' && tree->value)
		if (*(tget + 1) == '-' || !glob_brack(tree, tget, glob, sti))
			return ;
	if (*tget == '/' && tree->value)
		get_glob(tree, tget + 1, glob, sti);
}

void	ft_nstrstr(char *str, char *to_find, int *nb)
{
	char	*ptr;
	char	*tmp;

	if ((ptr = ft_strstr(str, to_find)))
	{
		tmp = ptr;
		if (ft_strlen(ptr) > ft_strlen(to_find))
		{
			if ((ptr = ft_strchr(ptr, '/')))
			{
				while (tmp && *tmp && *tmp != '/')
					if (ft_isalnum(*tmp))
						tmp = NULL;
					else
						tmp++;
				if (tmp)
					*nb += 1;
			}
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

int		brack_rev(char **src, char **targ)
{
	int tmp;

	*src += 2;
	while (**src && **src != ']')
	{
		if (**src == **targ)
			return (0);
		else if (*(*src + 1) == '-')
		{
			tmp = **src;
			while (tmp < *(*src + 2))
			{
				if (tmp == *(*src + 2))
					return (0);
				tmp++;
			}
			*src += 2;
		}
		*src += 1;
		tmp = **src;
	}
	*targ += 1;
	*src += 1;
	return (1);
}

int		brack_norm(char **src, char **targ)
{
	int tmp;

	while (**src && **src != ']' && **src != **targ)
	{
		if (**src == '-')
		{
			while (tmp < *(*src + 1) && tmp != **targ)
				tmp++;
			if (tmp == **targ)
				*targ += 1;
			if (tmp < *(*src + 1))
				break ;
		}
		tmp = **src;
		*src += 1;
	}
	**src == **targ ? *targ += 1 : 0;
	if (!**src || **src == ']')
		return (0);
	while (**src && **src != ']')
		*src += 1;
	if (!**src)
		return (0);
	*src += 1;
	return (1);
}

int		deal_bracket(char **src, char **targ)
{
	int		tmp;

	if (*(*src + 1) == '!')
	{
		if (!brack_rev(src, targ))
			return (0);
	}
	else
	{
		if (!brack_norm(src, targ))
			return (0);
	}
	return (1);
}

int		check_mln(char *src, char *targ);

int		deal_dbstar(char **src, char **targ)
{
	int		state;

	if (ft_strchr(*targ, '/'))
		if (check_mln(*src, ft_strchr(*targ, '/') + 1))
			return (1);
	while (**src == '*' || **src == '/')
	{
		state = 0;
		state |= **src == '*' ? IS_STAR : IS_SLASH;
		*src += 1;
	}
	if (state & IS_SLASH && **src == '?')
		return (2);
	while (**targ && **targ != **src)
	{
		if (**src == '?' || **src == '[')
			if (check_mln(*src, *targ + 1))
				return (1);
		*targ += 1;
	}
	if (!**targ && !**src)
		return (1);
	else if ((**targ && !**src) || (!**targ && **src))
		return (0);
	return (2);
}

int		deal_star(char **src, char **targ)
{
	if (*(*src + 1) == '*')
		return (deal_dbstar(src, targ));
	else
	{
		while (**targ && **targ != *(*src + 1) && **targ != '/')
		{
			if (*(*src + 1) == '?' || *(*src + 1) == '[')
				if (check_mln(*src + 1, *targ))
					return (1);
			*targ += 1;
		}
		if (**targ == '/')
			*src += 1;
		if (**targ == *(*src + 1))
		{
			if (**src == '*')
				if (check_mln(*src, *targ + 1))
					return (1);
			*src += 1;
		}
	}
	return (2);
}

int		deal_check(char **src, char **targ)
{
	if (**src == '*')
	{
		return (deal_star(src, targ));
	}
	else if (**src == '[')
	{
		if (!deal_bracket(src, targ))
			return (0);
	}
	else if (**src == **targ || (**src == '?' && **targ))
	{
		*src += 1;
		*targ += 1;
	}
	else
		return (0);
	return (2);
}

int		check_mln(char *src, char *targ)
{
	int i;
	int state;
	int tmp;

	state = 0;
	while (*src)
	{
		if (!*targ)
			break ;
		if ((tmp = deal_check(&src, &targ)) != 2)
			return (tmp);
	}
	while (*src == '*')
		src++;
	if (*src == '/')
		src++;
	if (!*src && !*targ)
		return (1);
	return (0);
}

t_slst	*expand_slst(t_slst *lst, char *str)
{
	if (lst)
	{
		lst->next = ft_memalloc(sizeof(t_slst));
		lst->next->prev = lst;
		lst = lst->next;
		lst->str = ft_strdup(str);
	}
	else
	{
		lst = ft_memalloc(sizeof(t_slst));
		lst->str = ft_strdup(str);
	}
	return (lst);
}

void	fill_mln(int check_dir, char *str, t_slst **ret)
{
	DIR		*dir;

	dir = NULL;
	if (check_dir == 1)
	{
		if ((dir = opendir(str)))
			*ret = expand_slst(*ret, str);
		if (dir)
			closedir(dir);
	}
	else
		*ret = expand_slst(*ret, str);
}

t_slst	*fill_slst(char *av, t_slist *glob, int star, int nb)
{
	int		is_point;
	DIR		*dir;
	char	*ptr;
	int		check_dir;
	t_slst	*ret;

	dir = NULL;
	check_dir = 0;
	is_point = 0;
	ret = NULL;
	if (ft_strchr(av, '?') && ft_strchr(av, '?') < ft_strchr(av, '/'))
		is_point = 1;
	if ((ptr = ft_strrchr(av, '/')) && !*(ptr + 1))
		check_dir = 1;
	while (glob && glob->str)
	{
		if (check_mln(av, glob->str))
			if ((ft_occuc(glob->str, '/') >= star && !is_point)
					|| (is_point && nb == ft_nslash(glob->str)))
				fill_mln(check_dir, glob->str, &ret);
		glob = glob->next;
	}
	return (ret);
}

t_slst	*deal_globing(char **av, t_tree *tree)
{
	t_slist		*glob;
	int			star;
	int			nb;
	t_stint		sti;

	glob = NULL;
	sti.str = NULL;
	sti.nb = 0;
	get_glob(tree, av[1], &glob, sti);
	star = 0;
	ft_nstrstr(av[1], "**", &star);
	nb = ft_nslash(av[1]);
	star = nb - star;
	while (glob && glob->prev)
		glob = glob->prev;
	return (fill_slst(av[1], glob, star, nb));
}

int		main(int ac, char **av, char **env)
{
	t_tree	*bin;
	t_tree	*files;
	t_slist	*glob = NULL;
	char	*term;
	t_slst	*fin;

	term = getenv("TERM");
	tgetent(NULL, term);
	//	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	bin = create_tree(env);
	files = create_file_tree(NULL);
	//	put_complet("", files);
	fin = deal_globing(av, files);
	while (fin->prev)
		fin = fin->prev;
	while (fin)
	{
		ft_putendl(fin->str);
		fin = fin->next;
	}
	return (0);
}
