/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 21:19:06 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/03 21:35:16 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "globing.h"

static t_slst	*expand_slst(t_slst *lst, char *str)
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

static void		fill_mln(int check_dir, char *str, t_slst **ret)
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

void			free_glob(t_slist *glob)
{
	if (!glob)
		return ;
	free_glob(glob->next);
	free(glob->str);
	free(glob);
}

static t_slst	*fill_slst(char *av, t_slist *glob, int star, int nb)
{
	int		is_point;
	DIR		*dir;
	char	*ptr;
	int		check_dir;
	t_slst	*ret;
	t_slist	*to_free

	dir = NULL;
	check_dir = 0;
	is_point = 0;
	ret = NULL;
	if (ft_strchr(av, '?') && ft_strchr(av, '?') < ft_strchr(av, '/'))
		is_point = 1;
	if ((ptr = ft_strrchr(av, '/')) && !*(ptr + 1))
		check_dir = 1;
	to_free = glob;
	while (glob && glob->str)
	{
		if (check_mln(av, glob->str))
			if ((ft_occuc(glob->str, '/') >= star && !is_point)
					|| (is_point && nb == ft_nslash(glob->str)))
				fill_mln(check_dir, glob->str, &ret);
		glob = glob->next;
	}
	free_glob(to_free);
	return (ret);
}

t_slst			*deal_globing(char *av, t_tree *tree)
{
	t_slist		*glob;
	int			star;
	int			nb;

	glob = NULL;
	ft_putendl(av);
	get_glob(tree, av, NULL, &glob, 0);
	star = 0;
	ft_nstrstr(av, "**", &star);
	nb = ft_nslash(av);
	star = nb - star;
	while (glob && glob->prev)
		glob = glob->prev;
	return (fill_slst(av, glob, star, nb));
}
