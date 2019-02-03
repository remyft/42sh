/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:57:24 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/03 23:04:14 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "struct.h"

static void	get_psblty(t_tree *tern, int *nb)
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

void		set_psblty(t_tree *tern)
{
	if (tern->right)
		set_psblty(tern->right);
	if (tern->left)
		set_psblty(tern->left);
	if (tern->tern_next)
		set_psblty(tern->tern_next);
	get_psblty(tern, &(tern->npsb));
}

void		*free_tree(t_tree *tern)
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

void		free_all_tree(t_line *line)
{
	if (line->tree[0])
		line->tree[0] = free_tree(line->tree[0]);
	if (line->tree[1])
		line->tree[1] = free_tree(line->tree[1]);
	if (line->tree[2])
		line->tree[2] = free_tree(line->tree[2]);
}
