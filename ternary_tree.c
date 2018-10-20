#include "libft/libft.h"
#include <dirent.h>

typedef struct	t_tree
{
	int				value;
	struct t_tree	*prev;
	struct t_tree	*next;
	struct t_tree	*tern_next;
	struct t_tree	*tern_prev;
}
				s_tree;


void	feed_tree(char *str, s_tree **tern)
{
	s_tree		*prev;
	s_tree		*tmp;
	s_tree		*begin;

	if ((*tern)->value >= 0)
	{
		begin = *tern;
		prev = NULL;
		while (*tern && *str > (*tern)->value)
		{
			prev = *tern;
			*tern = (*tern)->next;
		}
		if (!(*tern))
		{
			*tern = ft_memalloc(sizeof(s_tree));
			prev->next = *tern;
			(*tern)->prev = prev;
			(*tern)->value = *str;
		}
		else if (*str < (*tern)->value)
		{
			tmp = ft_memalloc(sizeof(s_tree));
			if ((*tern)->prev)
			{
				(*tern)->prev->next = tmp;
				tmp->prev = (*tern)->prev;
			}
			(*tern)->prev = tmp;
			tmp->next = (*tern);
			tmp->value = *str;
			*tern = tmp;
		}
	}
	else
		(*tern)->value = *str;
	if (!(*tern)->tern_next && *str)
	{
		(*tern)->tern_next = ft_memalloc(sizeof(s_tree));
		(*tern)->tern_next->value = -1;
		(*tern)->tern_next->tern_prev = *tern;
	}
	if (*str)
		feed_tree(str + 1, &((*tern)->tern_next));
//	if (prev)
//		*tern = begin;
	while ((*tern)->prev)
		(*tern) = (*tern)->prev;
}

void	ft_put(s_tree *tern, char *bru, int lvl)
{
	if (tern && !tern->tern_next)
	{
		bru[lvl] = '\0';
		ft_putstr(bru);
		ft_putchar(tern->value);
		ft_putchar('\n');
	}
	if (tern->tern_next)
	{
		bru[lvl] = tern->value;
		ft_put(tern->tern_next, bru, lvl + 1);
	}
	if (tern->next)
		ft_put(tern->next, bru, lvl);

}

int		main(int ac, char **av)
{
	char	*tab[] = {"salut", "sava", "salop", "brup", "brad", "briq", "fgabfdsjgfd", "brpfgd", "brpfdgdfs", "brpfgdasfsd", "mom", "tire", "a", "b", "soro", "sirop", "slurp"};
	int		i;
	s_tree	*ternary;
	s_tree	*begin;
	char	bru[257];
	int		lvl;
	struct dirent	*indir;
	DIR				*dir;
	char			cwd[4097];

	i = 0;
	ft_bzero(bru, 257);
	dir = opendir(getcwd(cwd, 4097));
	ternary = ft_memalloc(sizeof(s_tree));
	ternary->value = -1;
	begin = ternary;
	while ((indir = readdir(dir)))
	{
		ternary = begin;
		while (ternary->prev)
			ternary = ternary->prev;
		feed_tree(indir->d_name, &ternary);
		i++;
	}
	while (begin->prev)
		begin = begin->prev;
	ternary = begin;
//	reset_tern(&ternary);
	lvl = 0;
	if (ac == 2)
	{
		i = 0;
		while (av[1][i] && begin)
		{
			while (begin && begin->value != av[1][i])
				begin = begin->next;
			if (begin)
				begin = begin->tern_next;
			i++;
		}
		if (begin)
		{
			ft_strcpy(bru, av[1]);
			lvl = ft_strlen(av[1]);
			ft_put(begin, bru, lvl);
		}
	}
	else
		ft_put(begin, bru, 0);
	/*while (begin)
	{
		ft_putchar(begin->value);
		ft_putchar('\n');
		begin = begin->next;
	}*/
	/*ft_putchar(begin->value);
	ft_putchar(begin->tern_next->value);
	if (begin->tern_next->tern_next->prev)
		begin->tern_next->tern_next = begin->tern_next->tern_next->prev;
	ft_putchar(begin->tern_next->tern_next->value);

	ft_putchar(begin->tern_next->tern_next->next->value);*/
	return (0);
}
