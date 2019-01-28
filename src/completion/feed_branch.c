/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feed_branch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 02:06:53 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/28 20:09:15 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"

static t_tree	*create_new_branch(t_tree **tern, char *str, int lvl, unsigned int type)
{
	int		len;

	*tern = ft_memalloc(sizeof(t_tree));
	if (!*str)
		(*tern)->type = type;
	(*tern)->value = *str;
	if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
		(*tern)->max_len = lvl + len;
	return (*tern);
}

static void	feed_branch(t_tree **tern, char *str, int lvl, unsigned int type)
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
		*tern = create_new_branch(*str < prev->value ? &prev->left : &prev->right, str, lvl, type);
		(*tern)->prev = prev;
	}
	else
	{
		if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
			(*tern)->max_len = lvl + len;
	}
}

static void	set_new_mln(t_tree **tern, char *str, int lvl, unsigned int type)
{
	int		len;

	(*tern)->value = *str;
	if (!*str)
	{
		(*tern)->len = lvl;
		(*tern)->type = type;
	}
	if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
		(*tern)->max_len = lvl + len;
}

void		feed_tree(char *str, unsigned char type, t_tree **tern, int lvl)
{
	t_tree		*begin;

	begin = NULL;
	if ((*tern)->value >= 0)
	{
		begin = *tern;
		feed_branch(tern, str, lvl, type);
	}
	else
		set_new_mln(tern, str, lvl, type);
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
