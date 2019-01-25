/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 03:06:40 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 02:03:11 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"

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

void	deal_reset(t_tree *tree1, t_tree *tree2, t_tree *tree3)
{
	if (tree1)
		reset_put(tree1);
	if (tree2)
		reset_put(tree2);
	if (tree3)
		reset_put(tree3);
}
