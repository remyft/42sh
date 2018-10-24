#include "libft/libft.h"
#include <dirent.h>
#include <term.h>

typedef struct		s_tree
{
	int				value;
	int				max_len;
	int				tput;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*tern_next;
}					t_tree;

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

int		select_branch(t_tree **begin, t_tree **end, char *src)
{
	int		lenm;
	int		i;

	i = -1;
	while (src[++i] && *begin)
	{
		while (*begin && (*begin)->value != ft_toupper(src[i]))
			*begin = ft_toupper(src[i]) < (*begin)->value ? (*begin)->left : (*begin)->right;
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

void	put_complet(char *str, t_tree *tern)
{
	int		lenm;
	int		car_ret;
	t_tree	*begin;
	int		put;

	begin = tern;
	car_ret = 0;
	put = 1;
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
		if (indir->d_name[0] != '.')
			feed_tree(indir->d_name, &tern, 0);
	return (tern);
}

int		main(int ac, char **av, char **env)
{
	t_tree	*bin;
	t_tree	*files;
	t_tree	*save;
	int		lenm;
	int		car_ret;
	char	*term;

	term = getenv("TERM");
	tgetent(NULL, term);
	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	bin = create_tree(env);
	files = create_file_tree();
	save = bin;
	if (av[1] && !av[2])
	{
		put_complet(av[1], bin);
		put_complet(av[1], save);
	}
	else if (av[1] && av[2])
		put_complet(av[2], files);
	else
		put_complet(av[1], bin);
	ft_putchar('\n');
	return (0);
}
