/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 23:31:38 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/14 23:32:04 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "globing.h"

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
	return (0);
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
			return (0);
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
	if (get_new_glob(tree, glob) == 0)
		return (0);
	get_new_str(tree, glob, sti.str);
	si_tmp.str = ft_strdup((*glob)->str);
	si_tmp.nb = sti.nb;
	if ((dir = opendir((*glob)->str)) && ((*str == '/' && *(str + 1))
				|| sti.nb & IS_REC))
		deal_rec(tree, str, glob, &si_tmp);
	free(si_tmp.str);
	if (dir)
		closedir(dir);
}